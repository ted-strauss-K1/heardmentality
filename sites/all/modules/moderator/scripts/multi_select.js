/* Allow single-click selection of options in a multiple select element
 *
 * Author:
 *     Kevin Locke <klocke@digitalenginesoftware.com>
 *
 * Motivation:
 *     Select elements which allow multiple selections have been widely
 * recognized as a usability nightmare, particularly due to the requirement
 * that Ctrl be held down while clicking in order to select multiple elements.
 * Although this is intuitive to the computer savvy, less experienced users
 * are often at a loss to discover this behavior.  This script provides a
 * small usability improvement for these elements by removing the requirement
 * to hold Ctrl to select/deselect additional elements.
 *
 * Implementation:
 *     This script is implemented with jQuery.  Other implementations without
 * jQuery are certainly possible, and would (in some situations) be preferable.
 * However, as of this writing, this is the only implementation available.
 *     I have done my best to keep browser sniffing to a minimum and relied on
 * behavioral detection where possible.  The only exception currently is that
 * MouseDown event propagation is only prevented on Gecko-based browsers, since
 * I have not found a way to easily detect if it works and it does cause other
 * scripts to break when used (if they rely on MouseDown events).  The
 * behaviors documented below are current as of this writing, but is not
 * relied upon in the code.
 *     On WebKit browsers, preventing the default event action for the
 * MouseDown event on Option elements is sufficient to get the desired
 * behavior.  On Gecko browsers, preventing event propagation for the MouseDown
 * event on Option elements is sufficient.  For all others, the list of
 * selected options must be stored separately and restored to the select
 * element during the Click event (at which point the selections have been
 * reset as a result of the click).
 *     Some extra logic is required for dragging (which does not cause a click
 * event on Opera, but not on IE).  When multiple options are selected as the
 * result of a click-and-drag, they are added to the current list of
 * selections.
 *
 * Known Bugs:
 *  - Options flash off then on during click on IE and Opera
 *  - It is not possible to deselect multiple options simultaneously (e.g. by
 *    click-and-drag or Shift-click).  Although this may be preferable in some
 *    situations (removing contiguous elements from a large selected block),
 *    it can be quite counter-intuitive for ranges which span selected and
 *    unselected options.  So, for now, multiple option actions always result
 *    in additions to the selection list.  If enough people complain, I may
 *    add additional logic for providing toggle behavior for
 *    multiple-selections.
 *
 * TODO:
 *  - Implement drag-selection for browsers which don't handle it natively
 *    (WebKit) or when events are blocked (Gecko)
 *
 *     Additional bug reports, suggestions, improvements, etc. are greatly
 * appreciated.
 *
 * Changelog:
 *  2010-03-02  Fix mousedown event propagation on Firefox.
 *                Breakage should now be minimized since the event is
 *                re-propagated at the select element.  Also fixes a drag
 *                detection-caused bug where deselection didn't work.
 *              Rework state handling to fix drag-event-related errors
 *              Rework need for click event detection to be both more precise
 *                and make the determination with fewer events
 *  2009-12-31  Various bugfixes and improvements
 *                - Preserve scroll position and focus in Click/MouseUp events
 *                - Better handling of Ctrl-clicking (do nothing)
 *                - Only break mousedown when we know it is useful (on Gecko)
 *                - Don't toggle option when scroll bar is clicked (Opera)
 *  2009-12-30  Initial release
 *
 * License:
 * Copyright (c) 2009-2010, Kevin Locke <klocke@digitalenginesoftware.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * Observed Behaviors (not relied upon, but must handle appropriately):
 * Gecko (Firefox):
 *  - Mouse events occur for option elements (propagation causes selection)
 *  - Mouse events don't occur for options when over scrollbar
 *  - Click event doesn't occur when dragging across multiple elements
 *  - Click-and-drag across options causes new selection spanning those options
 *    Note:  This is suppressed by preventing mousedown event propagation
 *
 * Presto (Opera):
 *  - Mouse events occur for option elements (but has no effect on selection)
 *  - Mouse events occur for options when over scrollbar
 *  - Click event doesn't occur when dragging across multiple elements
 *  - Click-and-drag across options causes new selection spanning those options
 *
 * Trident (IE):
 *  - No mouse events fired from option elements
 *  - Click event occurrs even after dragging across multiple options
 *  - Click-and-drag across options causes new selection spanning those options
 *
 * WebKit/KHTML (Chrome, Konqueror, Safari):
 *  - Mouse events occur for option elements (default causes selection)
 *  - Mouse events don't occur for options when over scrollbar
 *  - Click event doesn't occur when dragging across multiple elements
 *  - Click-and-drag across options causes selection of mousedown option
 */
//jQuery(document).ready(function () {
//   multi_select();
//
// //  jQuery('select').ajaxStop(function() {
// //  multi_select();
////});
//});

function multi_select(){

     // Semi-globals (variables shared between all select elements on a page)
    //
    // true if the click event is required for synchronizing the state.
    // false if the click event is not required for synchronizing the state.
    // null if this has not yet been determined.
    var needClick = null;
    // Width of the scroll bar (currently only required on Opera)
    var scrollBarWidth;

    // Class for holding the (extra) state of a single select element
    function SelectState() {
        // location of the last mousedown event on this element
        this.mousedowni = null;     // Index of option in select
        this.mousedownx = null;
        this.mousedowny = null;
        this.mouseupi   = null;     // Index of option in select

        // Is the most recent unhandled event a drag event?
        // Note:  Drag events naturally select multiple options in 1 event
        this.isdragevent = false;

        // Has the most recent click/drag event been handled?
        this.handledevent = false;

        // List of indices of all selected options (sorted ascending)
        this.selectedIndices = null;
    }

    // Calculate the width of the browser scrollbar
    // Idea from http://www.alexandre-gomes.com/?p=115
    function getScrollBarWidth () {
        var testelem = jQuery('<div style="position: absolute; ' +
            'visibility: hidden; width: 200px; height: 150px; ' +
            'overflow: hidden"><p style="width: 100%; height: 200px">' +
            '</p></div>')[0];
        document.body.appendChild(testelem);
        var noscrollwidth = testelem.firstChild.clientWidth;
        testelem.style.overflow = 'scroll';
        var scrollwidth = testelem.firstChild.clientWidth;

        if (scrollwidth == noscrollwidth)
            scrollwidth = testelem.clientWidth;

        document.body.removeChild(testelem);

        return noscrollwidth - scrollwidth;
    };

    jQuery("select[multiple] option").mousedown(function(evt) {
        if (needClick !== false) {
            if (!this.parentNode.imsstate)
                this.parentNode.imsstate = new SelectState();
            var state = this.parentNode.imsstate;

            state.mousedowni = this.index;
        }

        // Don't mess with the normal Ctrl or Shift key functionality
        if (evt.ctrlKey || evt.shiftKey)
            return;

        var selelem = this.parentNode;
        if (this.clientWidth != 0)
            // When options are sized, events only happen when on option
            this.selected = !this.selected;
        else if (selelem.getBoundingClientRect) {
            // Otherwise, check that the click was not on the scrollbar

            if (scrollBarWidth == null)
                scrollBarWidth = getScrollBarWidth();

            var selbound = selelem.getBoundingClientRect();
            // Note:  Opera includes scrollbar in clientWidth
            var barleft = selbound.left +
                selelem.clientLeft + selelem.clientWidth - scrollBarWidth;
            if (evt.clientX < barleft)
                this.selected = !this.selected;
        }

        // Works for WebKit
        evt.preventDefault();

        // Works for Gecko
        // HACK:  Browser detection used to prevent unnecessary breakage
        //        resulting from messing with these events
        if (jQuery.browser.mozilla) {
            evt.stopPropagation();
            jQuery(selelem).trigger(evt);
        }
    });

    function optionMouseUp(evt) {
        if (!this.parentNode.imsstate)
            this.parentNode.imsstate = new SelectState();
        var state = this.parentNode.imsstate;

        // Only considered a drag event when crossing multiple options...
        state.mouseupi = this.index;
    }
    jQuery("select[multiple] option").mouseup(optionMouseUp);

    // Mark any option of elem with an index in selected as selected
    function addSelections(elem, selected) {
        var options = ("options" in elem) ? elem.options : elem;
        for (var i=0; i<selected.length; ++i)
            options[selected[i]].selected = true;
    }

    // Do 2 arrays contain equal elements
    // Note:  null == undefined == []
    function arrayEqual(arr1, arr2) {
        if (!arr1 || arr1.length == 0)
            return !arr2 || arr2.length == 0;

        if (!arr2)
            return false;

        if (arr1.length != arr2.length)
            return false;

        for (var i=0; i<arr1.length; ++i)
            if (arr1[i] !== arr2[i])
                return false;

        return true;
    }

    // Calculate the symmetric difference (XOR) of 2 sorted arrays
    function arraySymmetricDifference(a1, a2) {
        if (!a1 || a1.length == 0)
            return a2 || new Array(0);
        if (!a2 || a2.length == 0)
            return a1 || new Array(0);

        var i1 = 0, i2 = 0;
        var out = new Array();
        while (i1 < a1.length && i2 < a2.length) {
            if (a1[i1] < a2[i2]) {
                out.push(a1[i1++]);
            } else if (a1[i1] > a2[i2]) {
                out.push(a2[i2++]);
            } else {
                i1++;
                i2++;
            }
        }

        while (i1 < a1.length)
            out.push(a1[i1++]);
        while (i2 < a2.length)
            out.push(a2[i2++]);

        return out;
    }

    // Get a list of all selected indices from elem
    function getSelections(elem) {
        var selected = new Array();
        var options = ("options" in elem) ? elem.options : elem;
        for (var i=0; i<options.length; ++i)
            if (options[i].selected)
                selected.push(i);
        return selected;
    }

    // Find the smallest int i such that for all j, 0 < j < i, arr[j] < val
    // Requires that arr is sorted in ascending order
    function lowerBound(arr, val) {
        var low = 0, high = arr.length;
        var mid;

        while (low < high) {
            mid = Math.floor((low + high) / 2);
            if (arr[mid] < val)
                low = mid + 1;
            else
                high = mid;
        }

        return low;
    }

    // Combine two unique arrays in ascending order into 1
    function mergeSorted(a1, a2) {
        if (!a1 || a1.length == 0)
            return a2 || new Array(0);
        else if (!a2 || a2.length == 0)
            return a1 || new Array(0);

        var a = new Array(a1.length + a2.length);
        var i = 0, i1 = 0, i2 = 0;
        while (i1 < a1.length && i2 < a2.length) {
            if (a1[i1] < a2[i2])
                a[i++] = a1[i1++];
            else if (a1[i1] > a2[i2])
                a[i++] = a2[i2++];
            else {
                a[i++] = a1[i1++];
                i2++;
            }
        }

        // Add remnants
        while (i1 < a1.length)
            a[i++] = a1[i1++];
        while (i2 < a2.length)
            a[i++] = a2[i2++];

        // Trim overestimate
        a.length = i;

        return a;
    }

    // Note:  Named functions for easy unbinding later
    // Note2:  Set state here so that it is set in all browsers
    function selectMouseDown(evt) {
        if (!this.imsstate)
            this.imsstate = new SelectState();
        var state = this.imsstate;

        state.mousedownx = evt.clientX;
        state.mousedowny = evt.clientY;
    }
    jQuery("select[multiple]").mousedown(selectMouseDown);

    function selectMouseUp(evt) {
        if (!this.imsstate)
            this.imsstate = new SelectState();
        var state = this.imsstate;

        state.handledevent = false;
        if (state.mousedowni !== null && state.mouseupi !== null)
            state.isdragevent = state.mousedowni != state.mouseupi;
        else
            // Note:  X irrelevant to select drag
            // FIXME: Must assume that any y movement is between options since
            //        IE gives us no way to query this
            state.isdragevent = state.mousedowny != evt.clientY;

        // Note1:  Click event does not fire on Opera when dragged, does on IE
        // Note2:  IE does not update selections until after mouseup
        if (state.isdragevent)
            selectDrag.apply(this, [evt]);
    }
    jQuery("select[multiple]").mouseup(selectMouseUp);

    function selectDrag(evt) {
        if (!this.imsstate)
            this.imsstate = new SelectState();
        var state = this.imsstate;

        // Update selections with result of drag
        var scrollTop = this.scrollTop;
        var scrollLeft = this.scrollLeft;

        var curSelected = getSelections(this.options);

        // Check if state has changed (Note:  Not true in IE)
        if (arrayEqual(state.selectedIndices, curSelected))
            return;

        if (state.selectedIndices == null)
            state.selectedIndices = curSelected;
        else
            state.selectedIndices =
                mergeSorted(state.selectedIndices, curSelected);

        addSelections(this, state.selectedIndices);

        // Restore the scroll position
        this.scrollTop = scrollTop;
        this.scrollLeft = scrollLeft;

        state.handledevent = true;
    }

    // Do the hard work here
    function selectClick(evt) {
        if (!this.imsstate)
            this.imsstate = new SelectState();
        var state = this.imsstate;

        if (state.handledevent) {
            return;     // Drag event already handled
        } else if (state.isdragevent) {
            selectDrag.apply(this, [evt]);
            return;
        }

        // selectedIndices will hold our list of selected option indices
        if (state.selectedIndices == null)
            state.selectedIndices = new Array();

        var scrollTop = this.scrollTop;
        var scrollLeft = this.scrollLeft;

        // The index which was clicked to trigger this event
        // Note1: Not always true if mousedown worked - which we check shortly
        // Note2: Also not true when user unselected only selected object
        var minselected = this.selectedIndex;

        if (minselected == -1) {
            // Only selected element was deselected

            if (!evt.ctrlKey) {
                // Element deselected without Ctrl, no need for click handling
                unhookEventHandlers();
            }

            delete state.selectedIndices;
            return;
        }

        // List of select options
        var options = this.options;

        if (evt.ctrlKey || evt.shiftKey) {
            // The browser may select multiple elements on its own
            // Update our internal list of selected indices to match
            var curSelected = getSelections(options);
            if (evt.shiftKey) {
                state.selectedIndices =
                    mergeSorted(selectedIndices, curSelected);
                addSelections(this, state.selectedIndices);
            } else {
                state.selectedIndices = curSelected;
            }

            this.scrollTop = scrollTop;
            this.scrollLeft = scrollLeft;
            return;
        }

        var selectedIndices = state.selectedIndices;

        if (needClick === null) {
            // Check if our option mousedown handler worked

            // If an option other than the clicked element is selected
            // it works (note mousedowni == mouseupi since not drag)
            if (state.mousedowni != null && minselected != state.mousedowni) {
                unhookEventHandlers();
                return;
            }

            // If multiple options are selected, then it worked on its own
            for (var i=minselected+1; i<options.length; ++i) {
                if (options[i].selected) {
                    // Found multiple selections without restoring previous values
                    unhookEventHandlers();
                    return;
                }
            }

            // Only 1 option selected
            // If more than 1 option changed state from the click, then the
            // state is not being saved
            // (e.g. 1 deselected and another selected or >1 deselected)
            var changedindices =
                arraySymmetricDifference(selectedIndices, [minselected]);
            if (changedindices.length > 1)
                needClick = true;
        }

        var lb = lowerBound(selectedIndices, minselected);
        if (selectedIndices[lb] == minselected) {
            // Index was selected before click, so toggle it off
            options[minselected].selected = false;
            selectedIndices.splice(lb, 1);
        } else
            // Index was not selected, so toggle it on
            selectedIndices.splice(lb, 0, minselected);

        // Re-add forgotten selections
        addSelections(this, selectedIndices);

        // Re-focus minselected option element
        options[minselected].selected = options[minselected].selected;

        // Set scroll back to its previous position
        this.scrollTop = scrollTop;
        this.scrollLeft = scrollLeft;
    }

      jQuery("select[multiple]").click(selectClick);

    function unhookEventHandlers() {
        needClick = false;

        var selelems = jQuery("select[multiple]");
        selelems.unbind('click', selectClick);
        selelems.unbind('mousedown', selectMouseDown);
        selelems.unbind('mouseup', selectMouseUp);
        selelems.each(function() { delete this.imsstate; });

        var optelems = jQuery("select[multiple] option");
        optelems.unbind('mouseup', optionMouseUp);
    }

}
// vim: set ts=8 sts=4 sw=4 et:
