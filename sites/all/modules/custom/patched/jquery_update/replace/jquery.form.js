/*!
 * jQuery Form Plugin
 * version: 2.43 (12-MAR-2010)
 * @requires jQuery v1.3.2 or later
 *
 * Examples and documentation at: http://malsup.com/jquery/form/
 * Dual licensed under the MIT and GPL licenses:
 * http://www.opensource.org/licenses/mit-license.php
 * http://www.gnu.org/licenses/gpl.html
 */
(function (b) {
  function o() {
    if (b.fn.ajaxSubmit.debug) {
      var a = "[jquery.form] " + Array.prototype.join.call(arguments, "");
      if (window.console && window.console.log)window.console.log(a); else window.opera && window.opera.postError && window.opera.postError(a)
    }
  }

  b.fn.ajaxSubmit = function (a) {
    function d() {
      function r() {
        var p = h.attr("target"), n = h.attr("action");
        j.setAttribute("target", z);
        j.getAttribute("method") != "POST" && j.setAttribute("method", "POST");
        j.getAttribute("action") != g.url && j.setAttribute("action", g.url);
        g.skipEncodingOverride ||
        h.attr({encoding: "multipart/form-data", enctype: "multipart/form-data"});
        g.timeout && setTimeout(function () {
          C = true;
          s()
        }, g.timeout);
        var m = [];
        try {
          if (g.extraData)for (var u in g.extraData)m.push(b('<input type="hidden" name="' + u + '" value="' + g.extraData[u] + '" />').appendTo(j)[0]);
          t.appendTo("body");
          t.data("form-plugin-onload", s);
          j.submit()
        } finally {
          j.setAttribute("action", n);
          p ? j.setAttribute("target", p) : h.removeAttr("target");
          b(m).remove()
        }
      }

      function s() {
        if (!D) {
          var p = true;
          try {
            if (C)throw"timeout";
            var n, m;
            m = v.contentWindow ?
              v.contentWindow.document : v.contentDocument ? v.contentDocument : v.document;
            var u = g.dataType == "xml" || m.XMLDocument || b.isXMLDoc(m);
            o("isXml=" + u);
            if (!u && (m.body == null || m.body.innerHTML == "")) {
              if (--G) {
                o("requeing onLoad callback, DOM not available");
                setTimeout(s, 250);
                return
              }
              o("Could not access iframe DOM after 100 tries.");
              return
            }
            o("response detected");
            D = true;
            i.responseText = m.body ? m.body.innerHTML : null;
            i.responseXML = m.XMLDocument ? m.XMLDocument : m;
            i.getResponseHeader = function (H) {
              return{"content-type": g.dataType}[H]
            };
            if (g.dataType == "json" || g.dataType == "script") {
              var E = m.getElementsByTagName("textarea")[0];
              if (E)i.responseText = E.value; else {
                var F = m.getElementsByTagName("pre")[0];
                if (F)i.responseText = F.innerHTML
              }
            } else if (g.dataType == "xml" && !i.responseXML && i.responseText != null)i.responseXML = A(i.responseText);
            n = b.httpData(i, g.dataType)
          } catch (B) {
            o("error caught:", B);
            p = false;
            i.error = B;
            b.handleError(g, i, "error", B)
          }
          if (p) {
            g.success(n, "success");
            w && b.event.trigger("ajaxSuccess", [i, g])
          }
          w && b.event.trigger("ajaxComplete", [i, g]);
          w && !--b.active && b.event.trigger("ajaxStop");
          if (g.complete)g.complete(i, p ? "success" : "error");
          setTimeout(function () {
            t.removeData("form-plugin-onload");
            t.remove();
            i.responseXML = null
          }, 100)
        }
      }

      function A(p, n) {
        if (window.ActiveXObject) {
          n = new ActiveXObject("Microsoft.XMLDOM");
          n.async = "false";
          n.loadXML(p)
        } else n = (new DOMParser).parseFromString(p, "text/xml");
        return n && n.documentElement && n.documentElement.tagName != "parsererror" ? n : null
      }

      var j = h[0];
      if (b(":input[name=submit]", j).length)alert('Error: Form elements must not be named "submit".');
      else {
        var g = b.extend({}, b.ajaxSettings, a), q = b.extend(true, {}, b.extend(true, {}, b.ajaxSettings), g), z = "jqFormIO" + (new Date).getTime(), t = b('<iframe id="' + z + '" name="' + z + '" src="' + g.iframeSrc + '" onload="(jQuery(this).data(\'form-plugin-onload\'))()" />'), v = t[0];
        t.css({position: "absolute", top: "-1000px", left: "-1000px"});
        var i = {aborted: 0, responseText: null, responseXML: null, status: 0, statusText: "n/a", getAllResponseHeaders: function () {
        }, getResponseHeader: function () {
        }, setRequestHeader: function () {
        }, abort: function () {
          this.aborted =
            1;
          t.attr("src", g.iframeSrc)
        }}, w = g.global;
        w && !b.active++ && b.event.trigger("ajaxStart");
        w && b.event.trigger("ajaxSend", [i, g]);
        if (q.beforeSend && q.beforeSend(i, q) === false)q.global && b.active--; else if (!i.aborted) {
          var D = false, C = 0;
          if (q = j.clk) {
            var y = q.name;
            if (y && !q.disabled) {
              g.extraData = g.extraData || {};
              g.extraData[y] = q.value;
              if (q.type == "image") {
                g.extraData[y + ".x"] = j.clk_x;
                g.extraData[y + ".y"] = j.clk_y
              }
            }
          }
          g.forceSync ? r() : setTimeout(r, 10);
          var G = 100
        }
      }
    }

    if (!this.length) {
      o("ajaxSubmit: skipping submit process - no element selected");
      return this
    }
    if (typeof a == "function")a = {success: a};
    var e = b.trim(this.attr("action"));
    if (e)e = (e.match(/^([^#]+)/) || [])[1];
    e = e || window.location.href || "";
    a = b.extend({url: e, type: this.attr("method") || "GET", iframeSrc: /^https/i.test(window.location.href || "") ? "javascript:false" : "about:blank"}, a || {});
    e = {};
    this.trigger("form-pre-serialize", [this, a, e]);
    if (e.veto) {
      o("ajaxSubmit: submit vetoed via form-pre-serialize trigger");
      return this
    }
    if (a.beforeSerialize && a.beforeSerialize(this, a) === false) {
      o("ajaxSubmit: submit aborted via beforeSerialize callback");
      return this
    }
    var f = this.formToArray(a.semantic);
    if (a.data) {
      a.extraData = a.data;
      for (var c in a.data)if (a.data[c]instanceof Array)for (var l in a.data[c])f.push({name: c, value: a.data[c][l]}); else f.push({name: c, value: a.data[c]})
    }
    if (a.beforeSubmit && a.beforeSubmit(f, this, a) === false) {
      o("ajaxSubmit: submit aborted via beforeSubmit callback");
      return this
    }
    this.trigger("form-submit-validate", [f, this, a, e]);
    if (e.veto) {
      o("ajaxSubmit: submit vetoed via form-submit-validate trigger");
      return this
    }
    c = b.param(f);
    if (a.type.toUpperCase() ==
      "GET") {
      a.url += (a.url.indexOf("?") >= 0 ? "&" : "?") + c;
      a.data = null
    } else a.data = c;
    var h = this, k = [];
    a.resetForm && k.push(function () {
      h.resetForm()
    });
    a.clearForm && k.push(function () {
      h.clearForm()
    });
    if (!a.dataType && a.target) {
      var x = a.success || function () {
      };
      k.push(function (r) {
        var s = a.replaceTarget ? "replaceWith" : "html";
        b(a.target)[s](r).each(x, arguments)
      })
    } else a.success && k.push(a.success);
    a.success = function (r, s, A) {
      for (var j = 0, g = k.length; j < g; j++)k[j].apply(a, [r, s, A || h, h])
    };
    c = b("input:file", this).fieldValue();
    l = false;
    for (e = 0; e < c.length; e++)if (c[e])l = true;
    if (c.length && a.iframe !== false || a.iframe || l || 0)a.closeKeepAlive ? b.get(a.closeKeepAlive, d) : d(); else b.ajax(a);
    this.trigger("form-submit-notify", [this, a]);
    return this
  };
  b.fn.ajaxForm = function (a) {
    return this.ajaxFormUnbind().bind("submit.form-plugin",function (d) {
      d.preventDefault();
      b(this).ajaxSubmit(a)
    }).bind("click.form-plugin", function (d) {
      var e = d.target, f = b(e);
      if (!f.is(":submit,input:image")) {
        e = f.closest(":submit");
        if (e.length == 0)return;
        e = e[0]
      }
      var c = this;
      c.clk = e;
      if (e.type == "image")if (d.offsetX != undefined) {
        c.clk_x = d.offsetX;
        c.clk_y = d.offsetY
      } else if (typeof b.fn.offset == "function") {
        f = f.offset();
        c.clk_x = d.pageX - f.left;
        c.clk_y = d.pageY - f.top
      } else {
        c.clk_x = d.pageX - e.offsetLeft;
        c.clk_y = d.pageY - e.offsetTop
      }
      setTimeout(function () {
        c.clk = c.clk_x = c.clk_y = null
      }, 100)
    })
  };
  b.fn.ajaxFormUnbind = function () {
    return this.unbind("submit.form-plugin click.form-plugin")
  };
  b.fn.formToArray = function (a) {
    var d = [];
    if (this.length == 0)return d;
    var e = this[0], f = a ? e.getElementsByTagName("*") : e.elements;
    if (!f)return d;
    for (var c = 0, l = f.length; c < l; c++) {
      var h = f[c], k = h.name;
      if (k)if (a && e.clk && h.type == "image") {
        if (!h.disabled && e.clk == h) {
          d.push({name: k, value: b(h).val()});
          d.push({name: k + ".x", value: e.clk_x}, {name: k + ".y", value: e.clk_y})
        }
      } else if ((h = b.fieldValue(h, true)) && h.constructor == Array)for (var x = 0, r = h.length; x < r; x++)d.push({name: k, value: h[x]}); else h !== null && typeof h != "undefined" && d.push({name: k, value: h})
    }
    if (!a && e.clk) {
      a = b(e.clk);
      f = a[0];
      if ((k = f.name) && !f.disabled && f.type == "image") {
        d.push({name: k, value: a.val()});
        d.push({name: k + ".x", value: e.clk_x}, {name: k + ".y", value: e.clk_y})
      }
    }
    return d
  };
  b.fn.formSerialize = function (a) {
    return b.param(this.formToArray(a))
  };
  b.fn.fieldSerialize = function (a) {
    var d = [];
    this.each(function () {
      var e = this.name;
      if (e) {
        var f = b.fieldValue(this, a);
        if (f && f.constructor == Array)for (var c = 0, l = f.length; c < l; c++)d.push({name: e, value: f[c]}); else f !== null && typeof f != "undefined" && d.push({name: this.name, value: f})
      }
    });
    return b.param(d)
  };
  b.fn.fieldValue = function (a) {
    for (var d = [], e = 0, f = this.length; e < f; e++) {
      var c =
        b.fieldValue(this[e], a);
      c === null || typeof c == "undefined" || c.constructor == Array && !c.length || (c.constructor == Array ? b.merge(d, c) : d.push(c))
    }
    return d
  };
  b.fieldValue = function (a, d) {
    var e = a.name, f = a.type, c = a.tagName.toLowerCase();
    if (typeof d == "undefined")d = true;
    if (d && (!e || a.disabled || f == "reset" || f == "button" || (f == "checkbox" || f == "radio") && !a.checked || (f == "submit" || f == "image") && a.form && a.form.clk != a || c == "select" && a.selectedIndex == -1))return null;
    if (c == "select") {
      c = a.selectedIndex;
      if (c < 0)return null;
      d = [];
      a = a.options;
      e = (f = f == "select-one") ? c + 1 : a.length;
      for (c = f ? c : 0; c < e; c++) {
        var l = a[c];
        if (l.selected) {
          var h = l.value;
          h || (h = l.attributes && l.attributes.value && !l.attributes.value.specified ? l.text : l.value);
          if (f)return h;
          d.push(h)
        }
      }
      return d
    }
    return a.value
  };
  b.fn.clearForm = function () {
    return this.each(function () {
      b("input,select,textarea", this).clearFields()
    })
  };
  b.fn.clearFields = b.fn.clearInputs = function () {
    return this.each(function () {
      var a = this.type, d = this.tagName.toLowerCase();
      if (a == "text" || a == "password" || d == "textarea")this.value =
        ""; else if (a == "checkbox" || a == "radio")this.checked = false; else if (d == "select")this.selectedIndex = -1
    })
  };
  b.fn.resetForm = function () {
    return this.each(function () {
      if (typeof this.reset == "function" || typeof this.reset == "object" && !this.reset.nodeType)this.reset()
    })
  };
  b.fn.enable = function (a) {
    if (a == undefined)a = true;
    return this.each(function () {
      this.disabled = !a
    })
  };
  b.fn.selected = function (a) {
    if (a == undefined)a = true;
    return this.each(function () {
      var d = this.type;
      if (d == "checkbox" || d == "radio")this.checked = a; else if (this.tagName.toLowerCase() ==
        "option") {
        d = b(this).parent("select");
        a && d[0] && d[0].type == "select-one" && d.find("option").selected(false);
        this.selected = a
      }
    })
  }
})(jQuery);
