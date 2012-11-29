/*
 Highstock JS v1.1.5 (2012-03-15)

 (c) 2009-2011 Torstein H?nsi

 License: www.highcharts.com/license
 */
(function () {
  function G(a, b) {
    var c;
    a || (a = {});
    for (c in b)a[c] = b[c];
    return a
  }

  function Ja() {
    for (var a = 0, b = arguments, c = b.length, d = {}; a < c; a++)d[b[a++]] = b[a];
    return d
  }

  function Z(a, b) {
    return parseInt(a, b || 10)
  }

  function Gb(a) {
    return typeof a === "string"
  }

  function xb(a) {
    return typeof a === "object"
  }

  function mc(a) {
    return Object.prototype.toString.call(a) === "[object Array]"
  }

  function Yb(a) {
    return typeof a === "number"
  }

  function yb(a) {
    return va.log(a) / va.LN10
  }

  function bb(a) {
    return va.pow(10, a)
  }

  function Lb(a, b) {
    for (var c =
      a.length; c--;)if (a[c] === b) {
      a.splice(c, 1);
      break
    }
  }

  function A(a) {
    return a !== D && a !== null
  }

  function $(a, b, c) {
    var d, e;
    if (Gb(b))A(c) ? a.setAttribute(b, c) : a && a.getAttribute && (e = a.getAttribute(b)); else if (A(b) && xb(b))for (d in b)a.setAttribute(d, b[d]);
    return e
  }

  function zb(a) {
    return mc(a) ? a : [a]
  }

  function r() {
    var a = arguments, b, c, d = a.length;
    for (b = 0; b < d; b++)if (c = a[b], typeof c !== "undefined" && c !== null)return c
  }

  function W(a, b) {
    if (Ub && b && b.opacity !== D)b.filter = "alpha(opacity=" + b.opacity * 100 + ")";
    G(a.style, b)
  }

  function da(a, b, c, d, e) {
    a = S.createElement(a);
    b && G(a, b);
    e && W(a, {padding:0, border:Ka, margin:0});
    c && W(a, c);
    d && d.appendChild(a);
    return a
  }

  function ea(a, b) {
    var c = function () {
    };
    c.prototype = new a;
    G(c.prototype, b);
    return c
  }

  function Zb(a, b, c, d) {
    var e = ja.lang, f = isNaN(b = Ga(b)) ? 2 : b, b = c === void 0 ? e.decimalPoint : c, d = d === void 0 ? e.thousandsSep : d, e = a < 0 ? "-" : "", c = String(Z(a = Ga(+a || 0).toFixed(f))), g = c.length > 3 ? c.length % 3 : 0;
    return e + (g ? c.substr(0, g) + d : "") + c.substr(g).replace(/(\d{3})(?=\d)/g, "$1" + d) + (f ? b + Ga(a - c).toFixed(f).slice(2) : "")
  }

  function nb(a, b) {
    return Array((b || 2) + 1 - String(a).length).join(0) + a
  }

  function nc(a, b, c, d) {
    var e, c = r(c, 1);
    e = a / c;
    b || (b = [1, 2, 2.5, 5, 10], d && d.allowDecimals === !1 && (c === 1 ? b = [1, 2, 5, 10] : c <= 0.1 && (b = [1 / c])));
    for (d = 0; d < b.length; d++)if (a = b[d], e <= (b[d] + (b[d + 1] || b[d])) / 2)break;
    a *= c;
    return a
  }

  function zc(a, b) {
    var c = b || [
      [Hb, [1, 2, 5, 10, 20, 25, 50, 100, 200, 500]],
      [ob, [1, 2, 5, 10, 15, 30]],
      [cb, [1, 2, 5, 10, 15, 30]],
      [db, [1, 2, 3, 4, 6, 8, 12]],
      [P, [1, 2]],
      [Ca, [1, 2]],
      [pa, [1, 2, 3, 4, 6]],
      [fa, null]
    ], d = c[c.length - 1], e = K[d[0]], f = d[1], g;
    for (g = 0; g < c.length; g++)if (d =
      c[g], e = K[d[0]], f = d[1], c[g + 1] && a <= (e * f[f.length - 1] + K[c[g + 1][0]]) / 2)break;
    e === K[fa] && a < 5 * e && (f = [1, 2, 5]);
    e === K[fa] && a < 5 * e && (f = [1, 2, 5]);
    c = nc(a / e, f);
    return{unitRange:e, count:c, unitName:d[0]}
  }

  function $b(a, b, c, d) {
    var e = [], f = {}, g = ja.global.useUTC, h, j = new Date(b), b = a.unitRange, k = a.count;
    b >= K[ob] && (j.setMilliseconds(0), j.setSeconds(b >= K[cb] ? 0 : k * La(j.getSeconds() / k)));
    if (b >= K[cb])j[Ac](b >= K[db] ? 0 : k * La(j[oc]() / k));
    if (b >= K[db])j[Bc](b >= K[P] ? 0 : k * La(j[pc]() / k));
    if (b >= K[P])j[qc](b >= K[pa] ? 1 : k * La(j[eb]() / k));
    b >= K[pa] &&
    (j[Cc](b >= K[fa] ? 0 : k * La(j[ac]() / k)), h = j[bc]());
    b >= K[fa] && (h -= h % k, j[Dc](h));
    if (b === K[Ca])j[qc](j[eb]() - j[rc]() + r(d, 1));
    d = 1;
    h = j[bc]();
    for (var i = j.getTime(), m = j[ac](), j = j[eb](); i < c;)e.push(i), b === K[fa] ? i = cc(h + d * k, 0) : b === K[pa] ? i = cc(h, m + d * k) : !g && (b === K[P] || b === K[Ca]) ? i = cc(h, m, j + d * k * (b === K[P] ? 1 : 7)) : (i += b * k, b <= K[db] && i % K[P] === 0 && (f[i] = P)), d++;
    e.push(i);
    e.info = G(a, {higherRanks:f, totalRange:b * k});
    return e
  }

  function Ec() {
    this.symbol = this.color = 0
  }

  function Fc(a, b, c, d, e, f, g, h, j) {
    var k = g.x, g = g.y, j = k + c + (j ? h : -a - h),
      i = g - b + d + 15, m;
    j < 7 && (j = c + k + h);
    j + a > c + e && (j -= j + a - (c + e), i = g - b + d - h, m = !0);
    i < d + 5 ? (i = d + 5, m && g >= i && g <= i + b && (i = g + d + h)) : i + b > d + f && (i = d + f - b - h);
    return{x:j, y:i}
  }

  function Xc(a, b) {
    var c = a.length, d, e;
    for (e = 0; e < c; e++)a[e].ss_i = e;
    a.sort(function (a, c) {
      d = b(a, c);
      return d === 0 ? a.ss_i - c.ss_i : d
    });
    for (e = 0; e < c; e++)delete a[e].ss_i
  }

  function Mb(a) {
    for (var b = a.length, c = a[0]; b--;)a[b] < c && (c = a[b]);
    return c
  }

  function Ib(a) {
    for (var b = a.length, c = a[0]; b--;)a[b] > c && (c = a[b]);
    return c
  }

  function Ab(a) {
    for (var b in a)a[b] && a[b].destroy && a[b].destroy(),
      delete a[b]
  }

  function Nb(a) {
    dc || (dc = da(sb));
    a && dc.appendChild(a);
    dc.innerHTML = ""
  }

  function sc(a, b) {
    var c = "Highcharts error #" + a + ": www.highcharts.com/errors/" + a;
    if (b)throw c; else ba.console && console.log(c)
  }

  function Jb(a) {
    return parseFloat(a.toPrecision(14))
  }

  function Ob(a, b) {
    Vb = r(a, b.animation)
  }

  function Gc() {
    var a = ja.global.useUTC, b = a ? "getUTC" : "get", c = a ? "setUTC" : "set";
    cc = a ? Date.UTC : function (a, b, c, g, h, j) {
      return(new Date(a, b, r(c, 1), r(g, 0), r(h, 0), r(j, 0))).getTime()
    };
    oc = b + "Minutes";
    pc = b + "Hours";
    rc = b + "Day";
    eb = b + "Date";
    ac = b + "Month";
    bc = b + "FullYear";
    Ac = c + "Minutes";
    Bc = c + "Hours";
    qc = c + "Date";
    Cc = c + "Month";
    Dc = c + "FullYear"
  }

  function Qa() {
  }

  function ec(a, b) {
    function c(a) {
      function b(a, c) {
        this.pos = a;
        this.type = c || "";
        this.isNew = !0;
        c || this.addLabel()
      }

      function c(a) {
        if (a)this.options = a, this.id = a.id;
        return this
      }

      function d(a, b, c, e) {
        this.isNegative = b;
        this.options = a;
        this.x = c;
        this.stack = e;
        this.alignOptions = {align:a.align || (ha ? b ? "left" : "right" : "center"), verticalAlign:a.verticalAlign || (ha ? "middle" : b ? "bottom" : "top"), y:r(a.y,
          ha ? 4 : b ? 14 : -6), x:r(a.x, ha ? b ? -6 : 6 : 0)};
        this.textAlign = a.textAlign || (ha ? b ? "right" : "left" : "center")
      }

      function e() {
        var a = [], b = [], c;
        C = R = null;
        q(E.series, function (e) {
          if (e.visible || !p.ignoreHiddenSeries) {
            var f = e.options, g, h, j, i, k, m, l, n, y, v = f.threshold, Da, t = [], q = 0;
            if (ga && v <= 0)v = f.threshold = null;
            if (o)f = e.xData, f.length && (C = wa(r(C, f[0]), Mb(f)), R = O(r(R, f[0]), Ib(f))); else {
              var u, fc, s, Y = e.cropped, E = e.xAxis.getExtremes(), Yc = !!e.modifyValue;
              g = f.stacking;
              sa = g === "percent";
              if (g)k = f.stack, i = e.type + r(k, ""), m = "-" + i, e.stackKey =
                i, h = a[i] || [], a[i] = h, j = b[m] || [], b[m] = j;
              sa && (C = 0, R = 99);
              f = e.processedXData;
              l = e.processedYData;
              Da = l.length;
              for (c = 0; c < Da; c++)if (n = f[c], y = l[c], y !== null && y !== D && (g ? (fc = (u = y < v) ? j : h, s = u ? m : i, y = fc[n] = A(fc[n]) ? fc[n] + y : y, Ra[s] || (Ra[s] = {}), Ra[s][n] || (Ra[s][n] = new d(z.stackLabels, u, n, k)), Ra[s][n].setTotal(y)) : Yc && (y = e.modifyValue(y)), Y || (f[c + 1] || n) >= E.min && (f[c - 1] || n) <= E.max))if (n = y.length)for (; n--;)y[n] !== null && (t[q++] = y[n]); else t[q++] = y;
              !sa && t.length && (C = wa(r(C, t[0]), Mb(t)), R = O(r(R, t[0]), Ib(t)));
              A(v) && (C >= v ?
                (C = v, Qb = !0) : R < v && (R = v, Mc = !0))
            }
          }
        })
      }

      function f(a, b, c) {
        for (var d, b = Jb(La(b / a) * a), c = Jb(gc(c / a) * a), e = []; b <= c;) {
          e.push(b);
          b = Jb(b + a);
          if (b === d)break;
          d = b
        }
        return e
      }

      function g(a, b, c, d) {
        var e = [];
        if (!d)E._minorAutoInterval = null;
        if (a >= 0.5)a = x(a), e = f(a, b, c); else if (a >= 0.08) {
          var h = La(b), j, i, k, m, l, n;
          for (j = a > 0.3 ? [1, 2, 4] : a > 0.15 ? [1, 2, 4, 6, 8] : [1, 2, 3, 4, 5, 6, 7, 8, 9]; h < c + 1 && !n; h++) {
            k = j.length;
            for (i = 0; i < k && !n; i++)m = yb(bb(h) * j[i]), m > b && e.push(l), l > c && (n = !0), l = m
          }
        } else if (b = bb(b), c = bb(c), a = z[d ? "minorTickInterval" : "tickInterval"],
          a = r(a === "auto" ? null : a, E._minorAutoInterval, (c - b) * (z.tickPixelInterval / (d ? 5 : 1)) / ((d ? M / ca.length : M) || 1)), a = nc(a, null, va.pow(10, La(va.log(a) / va.LN10))), e = Kb(f(a, b, c), yb), !d)E._minorAutoInterval = a / 5;
        d || (Oa = a);
        return e
      }

      function h() {
        var a = [], b, c;
        if (ga) {
          c = ca.length;
          for (b = 1; b < c; b++)a = a.concat(g(pa, ca[b - 1], ca[b], !0))
        } else for (b = L + (ca[0] - L) % pa; b <= Q; b += pa)a.push(b);
        return a
      }

      function j() {
        var a, b = R - C >= Va, c, d, e, f, g, h;
        o && Va === D && !ga && (A(z.min) || A(z.max) ? Va = null : (q(E.series, function (a) {
          f = a.xData;
          for (d = g = a.xIncrement ?
            1 : f.length - 1; d > 0; d--)if (e = f[d] - f[d - 1], c === D || e < c)c = e
        }), Va = wa(c * 5, R - C)));
        Q - L < Va && (a = (Va - Q + L) / 2, a = [L - a, r(z.min, L - a)], b && (a[2] = C), L = Ib(a), h = [L + Va, r(z.max, L + Va)], b && (h[2] = R), Q = Mb(h), Q - L < Va && (a[0] = Q - Va, a[1] = r(z.min, Q - Va), L = Ib(a)))
      }

      function i(a) {
        var b, c = z.tickInterval, d = z.tickPixelInterval;
        ea ? (ba = n[o ? "xAxis" : "yAxis"][z.linkedTo], b = ba.getExtremes(), L = r(b.min, b.dataMin), Q = r(b.max, b.dataMax), z.type !== ba.options.type && sc(11, 1)) : (L = r(jb, z.min, C), Q = r(P, z.max, R));
        ga && (!a && wa(L, C) <= 0 && sc(10, 1), L = yb(L), Q = yb(Q));
        ub && (jb = L = O(L, Q - ub), P = Q, a && (ub = null));
        j();
        if (!Ta && !sa && !ea && A(L) && A(Q)) {
          b = Q - L || 1;
          if (!A(z.min) && !A(jb) && ja && (C < 0 || !Qb))L -= b * ja;
          if (!A(z.max) && !A(P) && Wa && (R > 0 || !Mc))Q += b * Wa
        }
        Oa = L === Q || L === void 0 || Q === void 0 ? 1 : ea && !c && d === ba.options.tickPixelInterval ? ba.tickInterval : r(c, Ta ? 1 : (Q - L) * d / (M || 1));
        o && !a && q(E.series, function (a) {
          a.processData(L !== V || Q !== da)
        });
        J();
        E.beforeSetTickPositions && E.beforeSetTickPositions();
        E.postProcessTickInterval && (Oa = E.postProcessTickInterval(Oa));
        !Y && !ga && (Jc = va.pow(10, La(va.log(Oa) /
          va.LN10)), A(z.tickInterval) || (Oa = nc(Oa, null, Jc, z)));
        E.tickInterval = Oa;
        pa = z.minorTickInterval === "auto" && Oa ? Oa / 5 : z.minorTickInterval;
        (ca = z.tickPositions || vb && vb.apply(E, [L, Q])) || (ca = Y ? (E.getNonLinearTimeTicks || $b)(zc(Oa, z.units), L, Q, z.startOfWeek, E.ordinalPositions, E.closestPointRange, !0) : ga ? g(Oa, L, Q) : f(Oa, L, Q));
        if (!ea && (a = ca[0], c = ca[ca.length - 1], z.startOnTick ? L = a : L > a && ca.shift(), z.endOnTick ? Q = c : Q < c && ca.pop(), pb || (pb = {x:0, y:0}), !Y && ca.length > pb[qa] && z.alignTicks !== !1))pb[qa] = ca.length
      }

      function k(a) {
        a =
          (new c(a)).render();
        za.push(a);
        return a
      }

      function m() {
        var a = z.title, d = z.stackLabels, e = z.alternateGridColor, f = z.lineWidth, g, j, i = n.hasRendered && A(V) && !isNaN(V), l = (g = E.series.length && A(L) && A(Q)) || r(z.showEmpty, !0), o, p;
        if (g || ea)if (pa && !Ta && q(h(), function (a) {
          Ma[a] || (Ma[a] = new b(a, "minor"));
          i && Ma[a].isNew && Ma[a].render(null, !0);
          Ma[a].isActive = !0;
          Ma[a].render()
        }), q(ca.slice(1).concat([ca[0]]), function (a, c) {
          c = c === ca.length - 1 ? 0 : c + 1;
          if (!ea || a >= L && a <= Q)Pa[a] || (Pa[a] = new b(a)), i && Pa[a].isNew && Pa[a].render(c, !0),
            Pa[a].isActive = !0, Pa[a].render(c)
        }), e && q(ca, function (a, b) {
          if (b % 2 === 0 && a < Q)fa[a] || (fa[a] = new c), o = a, p = ca[b + 1] !== D ? ca[b + 1] : Q, fa[a].options = {from:ga ? bb(o) : o, to:ga ? bb(p) : p, color:e}, fa[a].render(), fa[a].isActive = !0
        }), !E._addedPlotLB)q((z.plotLines || []).concat(z.plotBands || []), function (a) {
          k(a)
        }), E._addedPlotLB = !0;
        q([Pa, Ma, fa], function (a) {
          for (var b in a)a[b].isActive ? a[b].isActive = !1 : (a[b].destroy(), delete a[b])
        });
        f && (g = na + (v ? H : 0) + F, j = xa - Fb - (v ? qb : 0) + F, g = T.crispLine([ya, y ? na : g, y ? j : w, ka, y ? Ea - K : g, y ? j : xa - Fb],
          f), W ? W.animate({d:g}) : W = T.path(g).attr({stroke:z.lineColor, "stroke-width":f, zIndex:7}).add(), W[l ? "show" : "hide"]());
        if (u && l)l = y ? na : w, f = Z(a.style.fontSize || 12), l = {low:l + (y ? 0 : M), middle:l + M / 2, high:l + (y ? M : 0)}[a.align], f = (y ? w + qb : na) + (y ? 1 : -1) * (v ? -1 : 1) * Ka + (t === 2 ? f : 0), u[u.isNew ? "attr" : "animate"]({x:y ? l : f + (v ? H : 0) + F + (a.x || 0), y:y ? f - (v ? qb : 0) + F : l + (a.y || 0)}), u.isNew = !1;
        if (d && d.enabled) {
          var Da, s, d = E.stackTotalGroup;
          if (!d)E.stackTotalGroup = d = T.g("stack-labels").attr({visibility:$a, zIndex:6}).translate(B, U).add();
          for (Da in Ra)for (s in a = Ra[Da], a)a[s].render(d)
        }
        E.isDirty = !1
      }

      function l(a) {
        for (var b = za.length; b--;)za[b].id === a && za[b].destroy()
      }

      var o = a.isX, v = a.opposite, y = ha ? !o : o, t = y ? v ? 0 : 2 : v ? 1 : 3, Ra = {}, z = I(o ? hc : tc, [Zc, $c, Hc, ad][t], a), E = this, u, s = z.type, Y = s === "datetime", ga = s === "logarithmic", F = z.offset || 0, qa = o ? "x" : "y", M = 0, Ia, Ua, N, ib, na, w, H, qb, Fb, K, Pb, J, S, Za, $, W, C, R, Va = z.minRange || z.maxZoom, ub = z.range, jb, P, ma, hb, Q = null, L = null, V, da, ja = z.minPadding, Wa = z.maxPadding, ta = 0, ea = A(z.linkedTo), ba, Qb, Mc, sa, s = z.events, Fa, za = [],
        Oa, pa, Jc, ca, vb = z.tickPositioner, Pa = {}, Ma = {}, fa = {}, Sa, ra, Ka, Ta = z.categories, Qa = z.labels.formatter || function () {
          var a = this.value, b = this.dateTimeLabelFormat;
          return b ? Bb(b, a) : Oa % 1E6 === 0 ? a / 1E6 + "M" : Oa % 1E3 === 0 ? a / 1E3 + "k" : !Ta && a >= 1E3 ? Zb(a, 0) : a
        }, Ya = y && z.labels.staggerLines, oa = z.reversed, Ca = Ta && z.tickmarkPlacement === "between" ? 0.5 : 0;
      b.prototype = {addLabel:function () {
        var a = this.pos, b = z.labels, c = Ta && y && Ta.length && !b.step && !b.staggerLines && !b.rotation && Aa / Ta.length || !y && Aa / 2, d = a === ca[0], e = a === ca[ca.length - 1], f = Ta &&
          A(Ta[a]) ? Ta[a] : a, g = this.label, h = ca.info, j;
        Y && h && (j = z.dateTimeLabelFormats[h.higherRanks[a] || h.unitName]);
        this.isFirst = d;
        this.isLast = e;
        a = Qa.call({axis:E, chart:n, isFirst:d, isLast:e, dateTimeLabelFormat:j, value:ga ? Jb(bb(f)) : f});
        c = c && {width:O(1, x(c - 2 * (b.padding || 10))) + la};
        c = G(c, b.style);
        A(g) ? g && g.attr({text:a}).css(c) : this.label = A(a) && b.enabled ? T.text(a, 0, 0, b.useHTML).attr({align:b.align, rotation:b.rotation}).css(c).add(Za) : null
      }, getLabelSize:function () {
        var a = this.label;
        return a ? (this.labelBBox = a.getBBox())[y ?
          "height" : "width"] : 0
      }, getLabelSides:function () {
        var a = z.labels, b = this.labelBBox.width, a = b * {left:0, center:0.5, right:1}[a.align] - a.x;
        return[-a, b - a]
      }, handleOverflow:function (a) {
        var b = !0, c = this.isFirst, d = this.isLast, e = this.label, f = e.x;
        if (c || d) {
          var g = this.getLabelSides(), h = g[0], g = g[1], j = n.plotLeft, i = j + E.len, k = (a = Pa[ca[a + (c ? 1 : -1)]]) && a.label.x + a.getLabelSides()[c ? 0 : 1];
          c && !oa || d && oa ? f + h < j && (f = j - h, a && f + g > k && (b = !1)) : f + g > i && (f = i - g, a && f + h < k && (b = !1));
          e.x = f
        }
        return b
      }, render:function (a, b) {
        var c = this.type, d = this.label,
          e = this.pos, f = z.labels, g = this.gridLine, h = c ? c + "Grid" : "grid", j = c ? c + "Tick" : "tick", i = z[h + "LineWidth"], k = z[h + "LineColor"], l = z[h + "LineDashStyle"], m = z[j + "Length"], h = z[j + "Width"] || 0, n = z[j + "Color"], o = z[j + "Position"], j = this.mark, p = f.step, Da = b && Ja || xa, t = !0, u;
        u = y ? Pb(e + Ca, null, null, b) + N : na + F + (v ? (b && Na || Ea) - K - na : 0);
        Da = y ? Da - Fb + F - (v ? qb : 0) : Da - Pb(e + Ca, null, null, b) - N;
        if (i) {
          e = S(e + Ca, i, b);
          if (g === D) {
            g = {stroke:k, "stroke-width":i};
            if (l)g.dashstyle = l;
            if (!c)g.zIndex = 1;
            this.gridLine = g = i ? T.path(e).attr(g).add($) : null
          }
          !b && g &&
            e && g.animate({d:e})
        }
        if (h)o === "inside" && (m = -m), v && (m = -m), c = T.crispLine([ya, u, Da, ka, u + (y ? 0 : -m), Da + (y ? m : 0)], h), j ? j.animate({d:c}) : this.mark = T.path(c).attr({stroke:n, "stroke-width":h}).add(Za);
        if (d && !isNaN(u))u = u + f.x - (Ca && y ? Ca * Ua * (oa ? -1 : 1) : 0), Da = Da + f.y - (Ca && !y ? Ca * Ua * (oa ? 1 : -1) : 0), A(f.y) || (Da += Z(d.styles.lineHeight) * 0.9 - d.getBBox().height / 2), Ya && (Da += a / (p || 1) % Ya * 16), d.x = u, d.y = Da, this.isFirst && !r(z.showFirstLabel, 1) || this.isLast && !r(z.showLastLabel, 1) ? t = !1 : !Ya && y && f.overflow === "justify" && !this.handleOverflow(a) &&
          (t = !1), p && a % p && (t = !1), t ? (d[this.isNew ? "attr" : "animate"]({x:d.x, y:d.y}), d.show(), this.isNew = !1) : d.hide()
      }, destroy:function () {
        Ab(this)
      }};
      c.prototype = {render:function () {
        var a = this, b = (E.pointRange || 0) / 2, c = a.options, d = c.label, e = a.label, f = c.width, g = c.to, h = c.from, j = c.value, i, k = c.dashStyle, l = a.svgElem, m = [], n, p, o = c.color;
        p = c.zIndex;
        var Da = c.events;
        ga && (h = yb(h), g = yb(g), j = yb(j));
        if (f) {
          if (m = S(j, f), b = {stroke:o, "stroke-width":f}, k)b.dashstyle = k
        } else if (A(h) && A(g))h = O(h, L - b), g = wa(g, Q + b), i = S(g), (m = S(h)) && i ? m.push(i[4],
          i[5], i[1], i[2]) : m = null, b = {fill:o}; else return;
        if (A(p))b.zIndex = p;
        if (l)m ? l.animate({d:m}, null, l.onGetPath) : (l.hide(), l.onGetPath = function () {
          l.show()
        }); else if (m && m.length && (a.svgElem = l = T.path(m).attr(b).add(), Da))for (n in k = function (b) {
          l.on(b, function (c) {
            Da[b].apply(a, [c])
          })
        }, Da)k(n);
        if (d && A(d.text) && m && m.length && H > 0 && qb > 0) {
          d = I({align:y && i && "center", x:y ? !i && 4 : 10, verticalAlign:!y && i && "middle", y:y ? i ? 16 : 10 : i ? 6 : -4, rotation:y && !i && 90}, d);
          if (!e)a.label = e = T.text(d.text, 0, 0).attr({align:d.textAlign || d.align,
            rotation:d.rotation, zIndex:p}).css(d.style).add();
          i = [m[1], m[4], r(m[6], m[1])];
          m = [m[2], m[5], r(m[7], m[2])];
          n = Mb(i);
          p = Mb(m);
          e.align(d, !1, {x:n, y:p, width:Ib(i) - n, height:Ib(m) - p});
          e.show()
        } else e && e.hide();
        return a
      }, destroy:function () {
        Ab(this);
        Lb(za, this)
      }};
      d.prototype = {destroy:function () {
        Ab(this)
      }, setTotal:function (a) {
        this.cum = this.total = a
      }, render:function (a) {
        var b = this.options.formatter.call(this);
        this.label ? this.label.attr({text:b, visibility:Xa}) : this.label = n.renderer.text(b, 0, 0).css(this.options.style).attr({align:this.textAlign,
          rotation:this.options.rotation, visibility:Xa}).add(a)
      }, setOffset:function (a, b) {
        var c = this.isNegative, d = E.translate(this.total, 0, 0, 0, 1), e = E.translate(0), e = Ga(d - e), f = n.xAxis[0].translate(this.x) + a, g = n.plotHeight, c = {x:ha ? c ? d : d - e : f, y:ha ? g - f - b : c ? g - d - e : g - d, width:ha ? e : b, height:ha ? b : e};
        this.label && this.label.align(this.alignOptions, null, c).attr({visibility:$a})
      }};
      Pb = function (a, b, c, d, e) {
        var f = 1, g = 0, h = d ? ib : Ua, d = d ? V : L, e = z.ordinal || ga && e;
        h || (h = Ua);
        c && (f *= -1, g = M);
        oa && (f *= -1, g -= f * M);
        b ? (oa && (a = M - a), a = a / h + d, e && (a =
          E.lin2val(a))) : (e && (a = E.val2lin(a)), a = f * (a - d) * h + g + f * ta);
        return a
      };
      S = function (a, b, c) {
        var d, e, f, a = Pb(a, null, null, c), g = c && Ja || xa, h = c && Na || Ea, j, c = e = x(a + N);
        d = f = x(g - a - N);
        if (isNaN(a))j = !0; else if (y) {
          if (d = w, f = g - Fb, c < na || c > na + H)j = !0
        } else if (c = na, e = h - K, d < w || d > w + qb)j = !0;
        return j ? null : T.crispLine([ya, c, d, ka, e, f], b || 0)
      };
      J = function () {
        var a = Q - L, b = 0, c, d;
        if (o)ea ? b = ba.pointRange : q(E.series, function (a) {
          b = O(b, a.pointRange);
          d = a.closestPointRange;
          !a.noSharedTooltip && A(d) && (c = A(c) ? wa(c, d) : d)
        }), E.pointRange = b, E.closestPointRange =
          c;
        ib = Ua;
        E.translationSlope = Ua = M / (a + b || 1);
        N = y ? na : Fb;
        ta = Ua * (b / 2)
      };
      Ha.push(E);
      n[o ? "xAxis" : "yAxis"].push(E);
      ha && o && oa === D && (oa = !0);
      G(E, {addPlotBand:k, addPlotLine:k, adjustTickAmount:function () {
        if (pb && pb[qa] && !Y && !Ta && !ea && z.alignTicks !== !1) {
          var a = Sa, b = ca.length;
          Sa = pb[qa];
          if (b < Sa) {
            for (; ca.length < Sa;)ca.push(Jb(ca[ca.length - 1] + Oa));
            Ua *= (b - 1) / (Sa - 1);
            Q = ca[ca.length - 1]
          }
          if (A(a) && Sa !== a)E.isDirty = !0
        }
      }, categories:Ta, getExtremes:function () {
        return{min:ga ? Jb(bb(L)) : L, max:ga ? Jb(bb(Q)) : Q, dataMin:C, dataMax:R, userMin:jb,
          userMax:P}
      }, getPlotLinePath:S, getThreshold:function (a) {
        var b = ga ? bb(L) : L, c = ga ? bb(Q) : Q;
        b > a || a === null ? a = b : c < a && (a = c);
        return Pb(a, 0, 1, 0, 1)
      }, isXAxis:o, options:z, plotLinesAndBands:za, getOffset:function () {
        var a = E.series.length && A(L) && A(Q), c = a || r(z.showEmpty, !0), d = 0, e, f = 0, g = z.title, h = z.labels, j = [-1, 1, 1, -1][t], i;
        Za || (Za = T.g("axis").attr({zIndex:7}).add(), $ = T.g("grid").attr({zIndex:z.gridZIndex || 1}).add());
        ra = 0;
        if (a || ea)q(ca, function (a) {
          Pa[a] ? Pa[a].addLabel() : Pa[a] = new b(a)
        }), q(ca, function (a) {
          if (t === 0 || t ===
            2 || {1:"left", 3:"right"}[t] === h.align)ra = O(Pa[a].getLabelSize(), ra)
        }), Ya && (ra += (Ya - 1) * 16); else for (i in Pa)Pa[i].destroy(), delete Pa[i];
        if (g && g.text) {
          if (!u)u = E.axisTitle = T.text(g.text, 0, 0, g.useHTML).attr({zIndex:7, rotation:g.rotation || 0, align:g.textAlign || {low:"left", middle:"center", high:"right"}[g.align]}).css(g.style).add(), u.isNew = !0;
          if (c)d = u.getBBox()[y ? "height" : "width"], f = r(g.margin, y ? 5 : 10), e = g.offset;
          u[c ? "show" : "hide"]()
        }
        F = j * r(z.offset, ia[t]);
        Ka = r(e, ra + f + (t !== 2 && ra && j * z.labels[y ? "y" : "x"]));
        ia[t] =
          O(ia[t], Ka + d + j * F)
      }, render:m, setAxisSize:function () {
        var a = z.offsetLeft || 0, b = z.offsetRight || 0;
        na = r(z.left, B + a);
        w = r(z.top, U);
        H = r(z.width, Aa - a + b);
        qb = r(z.height, Ba);
        Fb = xa - qb - w;
        K = Ea - H - na;
        M = y ? H : qb;
        E.left = na;
        E.top = w;
        E.len = M
      }, setAxisTranslation:J, setCategories:function (b, c) {
        E.categories = a.categories = Ta = b;
        q(E.series, function (a) {
          a.translate();
          a.setTooltipPoints(!0)
        });
        E.isDirty = !0;
        r(c, !0) && n.redraw()
      }, setExtremes:function (a, b, c, d, e) {
        c = r(c, !0);
        e = G(e, {min:a, max:b});
        aa(E, "setExtremes", e, function () {
          jb = a;
          P = b;
          E.isDirtyExtremes =
            !0;
          c && n.redraw(d)
        })
      }, setScale:function () {
        var a, b, c, d;
        V = L;
        da = Q;
        Ia = M;
        M = y ? H : qb;
        d = M !== Ia;
        q(E.series, function (a) {
          if (a.isDirtyData || a.isDirty || a.xAxis.isDirty)c = !0
        });
        if (d || c || ea || jb !== ma || P !== hb) {
          e();
          i();
          ma = jb;
          hb = P;
          if (!o)for (a in Ra)for (b in Ra[a])Ra[a][b].cum = Ra[a][b].total;
          if (!E.isDirty)E.isDirty = d || L !== V || Q !== da
        }
      }, setTickPositions:i, translate:Pb, redraw:function () {
        Cb.resetTracker && Cb.resetTracker();
        m();
        q(za, function (a) {
          a.render()
        });
        q(E.series, function (a) {
          a.isDirty = !0
        })
      }, removePlotBand:l, removePlotLine:l,
        reversed:oa, setTitle:function (a, b) {
          z.title = I(z.title, a);
          u = u.destroy();
          E.isDirty = !0;
          r(b, !0) && n.redraw()
        }, series:[], stacks:Ra, destroy:function () {
          var a;
          ua(E);
          for (a in Ra)Ab(Ra[a]), Ra[a] = null;
          if (E.stackTotalGroup)E.stackTotalGroup = E.stackTotalGroup.destroy();
          q([Pa, Ma, fa, za], function (a) {
            Ab(a)
          });
          q([W, Za, $, u], function (a) {
            a && a.destroy()
          });
          W = Za = $ = u = null
        }});
      for (Fa in s)X(E, Fa, s[Fa]);
      if (ga)E.val2lin = yb, E.lin2val = bb
    }

    function d(a) {
      function b() {
        var c = this.points || zb(this), d = c[0].series, e;
        e = [d.tooltipHeaderFormatter(c[0].key)];
        q(c, function (a) {
          d = a.series;
          e.push(d.tooltipFormatter && d.tooltipFormatter(a) || a.point.tooltipFormatter(d.tooltipOptions.pointFormat))
        });
        e.push(a.footerFormat || "");
        return e.join("")
      }

      function c(a, b) {
        l = m ? a : (2 * l + a) / 3;
        p = m ? b : (p + b) / 2;
        o.attr({x:l, y:p});
        ab = Ga(a - l) > 1 || Ga(b - p) > 1 ? function () {
          c(a, b)
        } : null
      }

      function d() {
        if (!m) {
          var a = n.hoverPoints;
          o.hide();
          a && q(a, function (a) {
            a.setState()
          });
          n.hoverPoints = null;
          m = !0
        }
      }

      var e, f = a.borderWidth, g = a.crosshairs, h = [], j = a.style, i = a.shared, k = Z(j.padding), m = !0, l = 0, p = 0;
      j.padding =
        0;
      var o = T.label("", 0, 0, null, null, null, a.useHTML).attr({padding:k, fill:a.backgroundColor, "stroke-width":f, r:a.borderRadius, zIndex:8}).css(j).hide().add();
      rb || o.shadow(a.shadow);
      return{shared:i, refresh:function (f) {
        var j, k, l, p, y = {}, v = [];
        l = f.tooltipPos;
        j = a.formatter || b;
        var y = n.hoverPoints, t;
        i && (!f.series || !f.series.noSharedTooltip) ? (p = 0, y && q(y, function (a) {
          a.setState()
        }), n.hoverPoints = f, q(f, function (a) {
          a.setState(fb);
          p += a.plotY;
          v.push(a.getLabelConfig())
        }), k = f[0].plotX, p = x(p) / f.length, y = {x:f[0].category},
          y.points = v, f = f[0]) : y = f.getLabelConfig();
        y = j.call(y);
        e = f.series;
        k = r(k, f.plotX);
        p = r(p, f.plotY);
        j = x(l ? l[0] : ha ? Aa - p : k);
        k = x(l ? l[1] : ha ? Ba - k : p);
        l = i || !e.isCartesian || e.tooltipOutsidePlot || Ya(j, k);
        y === !1 || !l ? d() : (m && (o.show(), m = !1), o.attr({text:y}), t = a.borderColor || f.color || e.color || "#606060", o.attr({stroke:t}), l = Fc(o.width, o.height, B, U, Aa, Ba, {x:j, y:k}, r(a.distance, 12), ha), c(x(l.x), x(l.y)));
        if (g) {
          g = zb(g);
          var u;
          l = g.length;
          for (var s; l--;)if (u = f.series[l ? "yAxis" : "xAxis"], g[l] && u)if (u = u.getPlotLinePath(l ? r(f.stackY,
            f.y) : f.x, 1), h[l])h[l].attr({d:u, visibility:$a}); else {
            s = {"stroke-width":g[l].width || 1, stroke:g[l].color || "#C0C0C0", zIndex:g[l].zIndex || 2};
            if (g[l].dashStyle)s.dashstyle = g[l].dashStyle;
            h[l] = T.path(u).attr(s).add()
          }
        }
        aa(n, "tooltipRefresh", {text:y, x:j + B, y:k + U, borderColor:t})
      }, hide:d, hideCrosshairs:function () {
        q(h, function (a) {
          a && a.hide()
        })
      }, destroy:function () {
        q(h, function (a) {
          a && a.destroy()
        });
        o && (o = o.destroy())
      }}
    }

    function e(a) {
      function b(a) {
        var c, d, e, a = a || ba.event;
        if (!a.target)a.target = a.srcElement;
        if (a.originalEvent)a =
          a.originalEvent;
        if (a.event)a = a.event;
        c = a.touches ? a.touches.item(0) : a;
        tb = Ic(H);
        d = tb.left;
        e = tb.top;
        Ub ? (d = a.x, c = a.y) : (d = c.pageX - d, c = c.pageY - e);
        return G(a, {chartX:x(d), chartY:x(c)})
      }

      function c(a) {
        var b = {xAxis:[], yAxis:[]};
        q(Ha, function (c) {
          var d = c.translate, e = c.isXAxis;
          b[e ? "xAxis" : "yAxis"].push({axis:c, value:d((ha ? !e : e) ? a.chartX - B : Ba - a.chartY + U, !0)})
        });
        return b
      }

      function e() {
        var a = n.hoverSeries, b = n.hoverPoint;
        if (b)b.onMouseOut();
        if (a)a.onMouseOut();
        Sa && (Sa.hide(), Sa.hideCrosshairs());
        cb = null
      }

      function f() {
        if (l) {
          var a =
          {xAxis:[], yAxis:[]}, b = l.getBBox(), c = b.x - B, d = b.y - U;
          k && (q(Ha, function (e) {
            if (e.options.zoomEnabled !== !1) {
              var f = e.translate, g = e.isXAxis, h = ha ? !g : g, j = f(h ? c : Ba - d - b.height, !0, 0, 0, 1), f = f(h ? c + b.width : Ba - d, !0, 0, 0, 1);
              a[g ? "xAxis" : "yAxis"].push({axis:e, min:wa(j, f), max:O(j, f)})
            }
          }), aa(n, "selection", a, ob));
          l = l.destroy()
        }
        W(H, {cursor:"auto"});
        n.mouseIsDown = Ia = k = !1;
        ua(S, Fa ? "touchend" : "mouseup", f)
      }

      function g(a) {
        var b = A(a.pageX) ? a.pageX : a.page.x, a = A(a.pageX) ? a.pageY : a.page.y;
        tb && !Ya(b - tb.left - B, a - tb.top - U) && e()
      }

      function h() {
        e();
        tb = null
      }

      var j, i, k, l, m = rb ? "" : p.zoomType, o = /x/.test(m), y = /y/.test(m), v = o && !ha || y && ha, t = y && !ha || o && ha;
      if (!Qb)n.trackerGroup = Qb = T.g("tracker").attr({zIndex:9}).add();
      if (a.enabled)n.tooltip = Sa = d(a), nb = setInterval(function () {
        ab && ab()
      }, 32);
      (function () {
        H.onmousedown = function (a) {
          a = b(a);
          !Fa && a.preventDefault && a.preventDefault();
          n.mouseIsDown = Ia = !0;
          n.mouseDownX = j = a.chartX;
          i = a.chartY;
          X(S, Fa ? "touchend" : "mouseup", f)
        };
        var d = function (c) {
          if (!c || !(c.touches && c.touches.length > 1)) {
            c = b(c);
            if (!Fa)c.returnValue = !1;
            var d =
              c.chartX, e = c.chartY, f = !Ya(d - B, e - U);
            Fa && c.type === "touchstart" && ($(c.target, "isTracker") ? n.runTrackerClick || c.preventDefault() : !db && !f && c.preventDefault());
            f && (d < B ? d = B : d > B + Aa && (d = B + Aa), e < U ? e = U : e > U + Ba && (e = U + Ba));
            if (Ia && c.type !== "touchstart") {
              if (k = Math.sqrt(Math.pow(j - d, 2) + Math.pow(i - e, 2)), k > 10) {
                var g = Ya(j - B, i - U);
                if (pa && (o || y) && g)l || (l = T.rect(B, U, v ? 1 : Aa, t ? 1 : Ba, 0).attr({fill:p.selectionMarkerFill || "rgba(69,114,167,0.25)", zIndex:7}).add());
                l && v && (c = d - j, l.attr({width:Ga(c), x:(c > 0 ? 0 : c) + j}));
                l && t && (e -= i, l.attr({height:Ga(e),
                  y:(e > 0 ? 0 : e) + i}));
                g && !l && p.panning && n.pan(d)
              }
            } else if (!f) {
              var h, d = n.hoverPoint, e = n.hoverSeries, m, u, g = Ea, s = ha ? c.chartY : c.chartX - B;
              if (Sa && a.shared && (!e || !e.noSharedTooltip)) {
                h = [];
                m = R.length;
                for (u = 0; u < m; u++)if (R[u].visible && R[u].options.enableMouseTracking !== !1 && !R[u].noSharedTooltip && R[u].tooltipPoints.length)c = R[u].tooltipPoints[s], c._dist = Ga(s - c.plotX), g = wa(g, c._dist), h.push(c);
                for (m = h.length; m--;)h[m]._dist > g && h.splice(m, 1);
                if (h.length && h[0].plotX !== cb)Sa.refresh(h), cb = h[0].plotX
              }
              if (e && e.tracker &&
                (c = e.tooltipPoints[s]) && c !== d)c.onMouseOver()
            }
            return f || !pa
          }
        };
        H.onmousemove = d;
        X(H, "mouseleave", h);
        X(S, "mousemove", g);
        H.ontouchstart = function (a) {
          if (o || y)H.onmousedown(a);
          d(a)
        };
        H.ontouchmove = d;
        H.ontouchend = function () {
          k && e()
        };
        H.onclick = function (a) {
          var d = n.hoverPoint, a = b(a);
          a.cancelBubble = !0;
          if (!k)if (d && ($(a.target, "isTracker") || $(a.target.parentNode, "isTracker"))) {
            var e = d.plotX, f = d.plotY;
            G(d, {pageX:tb.left + B + (ha ? Aa - f : e), pageY:tb.top + U + (ha ? Ba - e : f)});
            aa(d.series, "click", G(a, {point:d}));
            d.firePointEvent("click",
              a)
          } else G(a, c(a)), Ya(a.chartX - B, a.chartY - U) && aa(n, "click", a);
          k = !1
        }
      })();
      G(this, {zoomX:o, zoomY:y, resetTracker:e, normalizeMouseEvent:b, destroy:function () {
        if (n.trackerGroup)n.trackerGroup = Qb = n.trackerGroup.destroy();
        ua(H, "mouseleave", h);
        ua(S, "mousemove", g);
        H.onclick = H.onmousedown = H.onmousemove = H.ontouchstart = H.ontouchend = H.ontouchmove = null
      }})
    }

    function f(a) {
      var b = a.type || p.type || p.defaultSeriesType, c = ma[b], d = n.hasRendered;
      if (d)if (ha && b === "column")c = ma.bar; else if (!ha && b === "bar")c = ma.column;
      b = new c;
      b.init(n,
        a);
      !d && b.inverted && (ha = !0);
      if (b.isCartesian)pa = b.isCartesian;
      R.push(b);
      return b
    }

    function g() {
      p.alignTicks !== !1 && q(Ha, function (a) {
        a.adjustTickAmount()
      });
      pb = null
    }

    function h(a) {
      var b = n.isDirtyLegend, c, d = n.isDirtyBox, e = R.length, f = e, h = n.clipRect;
      for (Ob(a, n); f--;)if (a = R[f], a.isDirty && a.options.stacking) {
        c = !0;
        break
      }
      if (c)for (f = e; f--;)if (a = R[f], a.options.stacking)a.isDirty = !0;
      q(R, function (a) {
        a.isDirty && a.options.legendType === "point" && (b = !0)
      });
      if (b && ub.renderLegend)ub.renderLegend(), n.isDirtyLegend = !1;
      pa &&
      (oa || (pb = null, q(Ha, function (a) {
        a.setScale()
      })), g(), Qa(), q(Ha, function (a) {
        if (a.isDirtyExtremes)a.isDirtyExtremes = !1, aa(a, "afterSetExtremes", a.getExtremes());
        if (a.isDirty || d)a.redraw(), d = !0
      }));
      d && (eb(), h && (Rb(h), h.animate({width:n.plotSizeX, height:n.plotSizeY + 1})));
      q(R, function (a) {
        a.isDirty && a.visible && (!a.isCartesian || a.xAxis) && a.redraw()
      });
      Cb && Cb.resetTracker && Cb.resetTracker();
      T.draw();
      aa(n, "redraw")
    }

    function j() {
      var a = s.xAxis || {}, b = s.yAxis || {}, a = zb(a);
      q(a, function (a, b) {
        a.index = b;
        a.isX = !0
      });
      b = zb(b);
      q(b, function (a, b) {
        a.index = b
      });
      a = a.concat(b);
      q(a, function (a) {
        new c(a)
      });
      g()
    }

    function k() {
      var a = ja.lang, b = p.resetZoomButton, c = b.theme, d = c.states, e = b.relativeTo === "chart" ? null : {x:B, y:U, width:Aa, height:Ba};
      n.resetZoomButton = T.button(a.resetZoom, null, null, wb, c, d && d.hover).attr({align:b.position.align, title:a.resetZoomTitle}).add().align(b.position, !1, e)
    }

    function i(a, b) {
      Za = I(s.title, a);
      K = I(s.subtitle, b);
      q([
        ["title", a, Za],
        ["subtitle", b, K]
      ], function (a) {
        var b = a[0], c = n[b], d = a[1], a = a[2];
        c && d && (c = c.destroy());
        a && a.text && !c && (n[b] = T.text(a.text, 0, 0, a.useHTML).attr({align:a.align, "class":gb + b, zIndex:a.zIndex || 4}).css(a.style).add().align(a, !1, Ua))
      })
    }

    function m() {
      za = p.renderTo;
      ea = gb + uc++;
      Gb(za) && (za = S.getElementById(za));
      za || sc(13, !0);
      za.innerHTML = "";
      za.offsetWidth || (hb = za.cloneNode(0), W(hb, {position:Db, top:"-9999px", display:""}), S.body.appendChild(hb));
      V = (hb || za).offsetWidth;
      P = (hb || za).offsetHeight;
      n.chartWidth = Ea = p.width || V || 600;
      n.chartHeight = xa = p.height || (P > 19 ? P : 400);
      n.container = H = da(sb, {className:gb +
        "container" + (p.className ? " " + p.className : ""), id:ea}, G({position:vc, overflow:Xa, width:Ea + la, height:xa + la, textAlign:"left", lineHeight:"normal"}, p.style), hb || za);
      n.renderer = T = p.forExport ? new Eb(H, Ea, xa, !0) : new Sb(H, Ea, xa);
      rb && T.create(n, H, Ea, xa);
      var a, b;
      Kc && H.getBoundingClientRect && (a = function () {
        W(H, {left:0, top:0});
        b = H.getBoundingClientRect();
        W(H, {left:-(b.left - Z(b.left)) + la, top:-(b.top - Z(b.top)) + la})
      }, a(), X(ba, "resize", a), X(n, "destroy", function () {
        ua(ba, "resize", a)
      }))
    }

    function l() {
      function a(c) {
        var d =
          p.width || za.offsetWidth, e = p.height || za.offsetHeight, c = c ? c.target : ba;
        if (d && e && (c === ba || c === S)) {
          if (d !== V || e !== P)clearTimeout(b), b = setTimeout(function () {
            mb(d, e, !1)
          }, 100);
          V = d;
          P = e
        }
      }

      var b;
      X(ba, "resize", a);
      X(n, "destroy", function () {
        ua(ba, "resize", a)
      })
    }

    function o() {
      n && aa(n, "endResize", null, function () {
        oa -= 1
      })
    }

    function t() {
      for (var a = ha || p.inverted || p.type === "bar" || p.defaultSeriesType === "bar", b = s.series, c = b && b.length; !a && c--;)b[c].type === "bar" && (a = !0);
      n.inverted = ha = a
    }

    function u() {
      var a = s.labels, b = s.credits, c;
      i();
      ub = n.legend = new Hb;
      q(Ha, function (a) {
        a.setScale()
      });
      Qa();
      q(Ha, function (a) {
        a.setTickPositions(!0)
      });
      g();
      Qa();
      eb();
      pa && q(Ha, function (a) {
        a.render()
      });
      if (!n.seriesGroup)n.seriesGroup = T.g("series-group").attr({zIndex:3}).add();
      q(R, function (a) {
        a.translate();
        a.setTooltipPoints();
        a.render()
      });
      a.items && q(a.items, function () {
        var b = G(a.style, this.style), c = Z(b.left) + B, d = Z(b.top) + U + 12;
        delete b.left;
        delete b.top;
        T.text(this.html, c, d).attr({zIndex:2}).css(b).add()
      });
      if (b.enabled && !n.credits)c = b.href, n.credits =
        T.text(b.text, 0, 0).on("click",function () {
          if (c)location.href = c
        }).attr({align:b.position.align, zIndex:8}).css(b.style).add().align(b.position);
      n.hasRendered = !0
    }

    function v() {
      if (!Tb && ba == ba.top && S.readyState !== "complete" || rb && !ba.canvg)rb ? Lc.push(v, s.global.canvasToolsURL) : S.attachEvent("onreadystatechange", function () {
        S.detachEvent("onreadystatechange", v);
        S.readyState === "complete" && v()
      }); else {
        m();
        aa(n, "init");
        if (Highcharts.RangeSelector && s.rangeSelector.enabled)n.rangeSelector = new Highcharts.RangeSelector(n);
        kb();
        lb();
        t();
        j();
        q(s.series || [], function (a) {
          f(a)
        });
        if (Highcharts.Scroller && (s.navigator.enabled || s.scrollbar.enabled))n.scroller = new Highcharts.Scroller(n);
        n.render = u;
        n.tracker = Cb = new e(s.tooltip);
        u();
        T.draw();
        b && b.apply(n, [n]);
        q(n.callbacks, function (a) {
          a.apply(n, [n])
        });
        hb && (za.appendChild(H), Nb(hb));
        aa(n, "load")
      }
    }

    var s, Y = a.series;
    a.series = null;
    s = I(ja, a);
    s.series = a.series = Y;
    var p = s.chart, Y = p.margin, Y = xb(Y) ? Y : [Y, Y, Y, Y], qa = r(p.marginTop, Y[0]), M = r(p.marginRight, Y[1]), w = r(p.marginBottom, Y[2]), N = r(p.marginLeft,
      Y[3]), F = p.spacingTop, ga = p.spacingRight, y = p.spacingBottom, ib = p.spacingLeft, Ua, Za, K, U, J, C, B, ia, za, hb, H, ea, V, P, Ea, xa, Na, Ja, ta, sa, fa, vb, n = this, db = (Y = p.events) && !!Y.click, Ca, Ya, Sa, Ia, na, Va, jb, Ba, Aa, Cb, Qb, ub, Wa, Ma, tb, pa = p.showAxes, oa = 0, Ha = [], pb, R = [], ha, T, ab, nb, cb, eb, Qa, kb, lb, mb, ob, wb, Hb = function () {
      function a(b, c) {
        var d = b.legendItem, e = b.legendLine, g = b.legendSymbol, h = p.color, j = c ? f.itemStyle.color : h, h = c ? b.color : h;
        d && d.css({fill:j});
        e && e.attr({stroke:h});
        g && g.attr({stroke:h, fill:h})
      }

      function b(a) {
        var c = a.legendItem,
          d = a.legendLine, e = a._legendItemPos, f = e[0], e = e[1], g = a.legendSymbol, a = a.checkbox;
        c && c.attr({x:v ? f : Wa - f, y:e});
        d && d.translate(v ? f : Wa - f, e - 4);
        g && (c = f + g.xOff, g.attr({x:v ? c : Wa - c, y:e + g.yOff}));
        if (a)a.x = f, a.y = e
      }

      function c() {
        q(i, function (a) {
          var b = a.checkbox, c = x.alignAttr;
          b && W(b, {left:c.translateX + a.legendItemWidth + b.x - 40 + la, top:c.translateY + b.y - 11 + la})
        })
      }

      function d(b) {
        var c, e, i, k, n = b.legendItem;
        k = b.series || b;
        var s = k.options, q = s && s.borderWidth || 0;
        if (!n) {
          k = /^(bar|pie|area|column)$/.test(k.type);
          b.legendItem = n =
            T.text(f.labelFormatter.call(b), 0, 0, f.useHTML).css(b.visible ? l : p).on("mouseover",function () {
              b.setState(fb);
              n.css(m)
            }).on("mouseout",function () {
                n.css(b.visible ? l : p);
                b.setState()
              }).on("click",function () {
                var a = function () {
                  b.setVisible()
                };
                b.firePointEvent ? b.firePointEvent("legendItemClick", null, a) : aa(b, "legendItemClick", null, a)
              }).attr({align:v ? "left" : "right", zIndex:2}).add(x);
          if (!k && s && s.lineWidth) {
            var z = {"stroke-width":s.lineWidth, zIndex:2};
            if (s.dashStyle)z.dashstyle = s.dashStyle;
            b.legendLine = T.path([ya,
              (-h - j) * (v ? 1 : -1), 0, ka, -j * (v ? 1 : -1), 0]).attr(z).add(x)
          }
          if (k)i = T.rect(c = -h - j, e = -11, h, 12, 2).attr({zIndex:3}).add(x), v || (c += h); else if (s && s.marker && s.marker.enabled)i = s.marker.radius, i = T.symbol(b.symbol, c = -h / 2 - j - i, e = -4 - i, 2 * i, 2 * i).attr(b.pointAttr[ra]).attr({zIndex:3}).add(x), v || (c += h / 2);
          if (i)i.xOff = c + q % 2 / 2, i.yOff = e + q % 2 / 2;
          b.legendSymbol = i;
          a(b, b.visible);
          if (s && s.showCheckbox)b.checkbox = da("input", {type:"checkbox", checked:b.selected, defaultChecked:b.selected}, f.itemCheckboxStyle, H), X(b.checkbox, "click", function (a) {
            aa(b,
              "checkboxClick", {checked:a.target.checked}, function () {
                b.select()
              })
          })
        }
        c = n.getBBox();
        e = b.legendItemWidth = f.itemWidth || h + j + c.width + o;
        na = c.height;
        if (g && M - r + e > (ib || Ea - 2 * o - r))M = r, qa += u + na + t;
        !g && qa + f.y + na > xa - F - y && (qa = ga, M += Y, Y = 0);
        Y = O(Y, e);
        B = O(B, qa + t);
        b._legendItemPos = [M, qa];
        g ? M += e : qa += u + na + t;
        N = ib || O(M - r + (g ? 0 : e), N)
      }

      function e() {
        M = r;
        qa = ga;
        B = N = 0;
        x || (x = T.g("legend").attr({zIndex:7}).add());
        i = [];
        q(D, function (a) {
          var b = a.options;
          b.showInLegend && (i = i.concat(a.legendItems || (b.legendType === "point" ? a.data : a)))
        });
        Xc(i,
          function (a, b) {
            return(a.options.legendIndex || 0) - (b.options.legendIndex || 0)
          });
        Fb && i.reverse();
        q(i, d);
        Wa = ib || N;
        Ma = B - s + na;
        if (w || A) {
          Wa += 2 * o;
          Ma += 2 * o;
          if (Ia) {
            if (Wa > 0 && Ma > 0)Ia[Ia.isNew ? "attr" : "animate"](Ia.crisp(null, null, null, Wa, Ma)), Ia.isNew = !1
          } else Ia = T.rect(0, 0, Wa, Ma, f.borderRadius, w || 0).attr({stroke:f.borderColor, "stroke-width":w || 0, fill:A || Ka}).add(x).shadow(f.shadow), Ia.isNew = !0;
          Ia[i.length ? "show" : "hide"]()
        }
        q(i, b);
        for (var a = ["left", "right", "top", "bottom"], g, h = 4; h--;)g = a[h], k[g] && k[g] !== "auto" && (f[h <
          2 ? "align" : "verticalAlign"] = g, f[h < 2 ? "x" : "y"] = Z(k[g]) * (h % 2 ? -1 : 1));
        i.length && x.align(G(f, {width:Wa, height:Ma}), !0, Ua);
        oa || c()
      }

      var f = n.options.legend;
      if (f.enabled) {
        var g = f.layout === "horizontal", h = f.symbolWidth, j = f.symbolPadding, i, k = f.style, l = f.itemStyle, m = f.itemHoverStyle, p = I(l, f.itemHiddenStyle), o = f.padding || Z(k.padding), v = !f.rtl, u = f.itemMarginTop || 0, t = f.itemMarginBottom || 0, s = 18, Y = 0, r = 4 + o + h + j, ga = o + u + s - 5, M, qa, B, na = 0, Ia, w = f.borderWidth, A = f.backgroundColor, x, N, ib = f.width, D = n.series, Fb = f.reversed;
        e();
        X(n,
          "endResize", c);
        return{colorizeItem:a, destroyItem:function (a) {
          var b = a.checkbox;
          q(["legendItem", "legendLine", "legendSymbol"], function (b) {
            a[b] && a[b].destroy()
          });
          b && Nb(a.checkbox)
        }, renderLegend:e, destroy:function () {
          Ia && (Ia = Ia.destroy());
          x && (x = x.destroy())
        }}
      }
    };
    Ya = function (a, b) {
      return a >= 0 && a <= Aa && b >= 0 && b <= Ba
    };
    wb = function () {
      var a = n.resetZoomButton;
      aa(n, "selection", {resetSelection:!0}, ob);
      if (a)n.resetZoomButton = a.destroy()
    };
    ob = function (a) {
      var b;
      n.resetZoomEnabled !== !1 && !n.resetZoomButton && k();
      !a || a.resetSelection ?
        q(Ha, function (a) {
          a.options.zoomEnabled !== !1 && (a.setExtremes(null, null, !1), b = !0)
        }) : q(a.xAxis.concat(a.yAxis), function (a) {
        var c = a.axis;
        if (n.tracker[c.isXAxis ? "zoomX" : "zoomY"])c.setExtremes(a.min, a.max, !1), b = !0
      });
      b && h(r(p.animation, n.pointCount < 100))
    };
    n.pan = function (a) {
      var b = n.xAxis[0], c = n.mouseDownX, d = b.pointRange / 2, e = b.getExtremes(), f = b.translate(c - a, !0) + d, c = b.translate(c + Aa - a, !0) - d;
      (d = n.hoverPoints) && q(d, function (a) {
        a.setState()
      });
      f > wa(e.dataMin, e.min) && c < O(e.dataMax, e.max) && b.setExtremes(f, c, !0,
        !1);
      n.mouseDownX = a;
      W(H, {cursor:"move"})
    };
    Qa = function () {
      var a = s.legend, b = r(a.margin, 10), c = a.x, d = a.y, e = a.align, f = a.verticalAlign, g;
      kb();
      if ((n.title || n.subtitle) && !A(qa))(g = O(n.title && !Za.floating && !Za.verticalAlign && Za.y || 0, n.subtitle && !K.floating && !K.verticalAlign && K.y || 0)) && (U = O(U, g + r(Za.margin, 15) + F));
      a.enabled && !a.floating && (e === "right" ? A(M) || (J = O(J, Wa - c + b + ga)) : e === "left" ? A(N) || (B = O(B, Wa + c + b + ib)) : f === "top" ? A(qa) || (U = O(U, Ma + d + b + F)) : f === "bottom" && (A(w) || (C = O(C, Ma - d + b + y))));
      n.extraBottomMargin && (C +=
        n.extraBottomMargin);
      n.extraTopMargin && (U += n.extraTopMargin);
      pa && q(Ha, function (a) {
        a.getOffset()
      });
      A(N) || (B += ia[3]);
      A(qa) || (U += ia[0]);
      A(w) || (C += ia[2]);
      A(M) || (J += ia[1]);
      lb()
    };
    mb = function (a, b, c) {
      var d = n.title, e = n.subtitle;
      oa += 1;
      Ob(c, n);
      Ja = xa;
      Na = Ea;
      if (A(a))n.chartWidth = Ea = x(a);
      if (A(b))n.chartHeight = xa = x(b);
      W(H, {width:Ea + la, height:xa + la});
      T.setSize(Ea, xa, c);
      Aa = Ea - B - J;
      Ba = xa - U - C;
      pb = null;
      q(Ha, function (a) {
        a.isDirty = !0;
        a.setScale()
      });
      q(R, function (a) {
        a.isDirty = !0
      });
      n.isDirtyLegend = !0;
      n.isDirtyBox = !0;
      Qa();
      d &&
      d.align(null, null, Ua);
      e && e.align(null, null, Ua);
      h(c);
      Ja = null;
      aa(n, "resize");
      Vb === !1 ? o() : setTimeout(o, Vb && Vb.duration || 500)
    };
    lb = function () {
      n.plotLeft = B = x(B);
      n.plotTop = U = x(U);
      n.plotWidth = Aa = x(Ea - B - J);
      n.plotHeight = Ba = x(xa - U - C);
      n.plotSizeX = ha ? Ba : Aa;
      n.plotSizeY = ha ? Aa : Ba;
      Ua = {x:ib, y:F, width:Ea - ib - ga, height:xa - F - y};
      q(Ha, function (a) {
        a.setAxisSize();
        a.setAxisTranslation()
      })
    };
    kb = function () {
      U = r(qa, F);
      J = r(M, ga);
      C = r(w, y);
      B = r(N, ib);
      ia = [0, 0, 0, 0]
    };
    eb = function () {
      var a = p.borderWidth || 0, b = p.backgroundColor, c = p.plotBackgroundColor,
        d = p.plotBackgroundImage, e, f = {x:B, y:U, width:Aa, height:Ba};
      e = a + (p.shadow ? 8 : 0);
      if (a || b)ta ? ta.animate(ta.crisp(null, null, null, Ea - e, xa - e)) : ta = T.rect(e / 2, e / 2, Ea - e, xa - e, p.borderRadius, a).attr({stroke:p.borderColor, "stroke-width":a, fill:b || Ka}).add().shadow(p.shadow);
      c && (sa ? sa.animate(f) : sa = T.rect(B, U, Aa, Ba, 0).attr({fill:c}).add().shadow(p.plotShadow));
      d && (fa ? fa.animate(f) : fa = T.image(d, B, U, Aa, Ba).add());
      p.plotBorderWidth && (vb ? vb.animate(vb.crisp(null, B, U, Aa, Ba)) : vb = T.rect(B, U, Aa, Ba, 0, p.plotBorderWidth).attr({stroke:p.plotBorderColor,
        "stroke-width":p.plotBorderWidth, zIndex:4}).add());
      n.isDirtyBox = !1
    };
    p.reflow !== !1 && X(n, "load", l);
    if (Y)for (Ca in Y)X(n, Ca, Y[Ca]);
    n.options = s;
    n.series = R;
    n.xAxis = [];
    n.yAxis = [];
    n.addSeries = function (a, b, c) {
      var d;
      a && (Ob(c, n), b = r(b, !0), aa(n, "addSeries", {options:a}, function () {
        d = f(a);
        d.isDirty = !0;
        n.isDirtyLegend = !0;
        b && n.redraw()
      }));
      return d
    };
    n.animation = rb ? !1 : r(p.animation, !0);
    n.Axis = c;
    n.destroy = function () {
      var a, b = H && H.parentNode;
      if (n !== null) {
        aa(n, "destroy");
        ua(n);
        for (a = Ha.length; a--;)Ha[a] = Ha[a].destroy();
        for (a = R.length; a--;)R[a] = R[a].destroy();
        q("title,subtitle,seriesGroup,clipRect,credits,tracker,scroller,rangeSelector".split(","), function (a) {
          var b = n[a];
          b && (n[a] = b.destroy())
        });
        q([ta, vb, sa, ub, Sa, T, Cb], function (a) {
          a && a.destroy && a.destroy()
        });
        ta = vb = sa = ub = Sa = T = Cb = null;
        if (H)H.innerHTML = "", ua(H), b && Nb(H), H = null;
        clearInterval(nb);
        for (a in n)delete n[a];
        s = n = null
      }
    };
    n.get = function (a) {
      var b, c, d;
      for (b = 0; b < Ha.length; b++)if (Ha[b].options.id === a)return Ha[b];
      for (b = 0; b < R.length; b++)if (R[b].options.id === a)return R[b];
      for (b = 0; b < R.length; b++) {
        d = R[b].points || [];
        for (c = 0; c < d.length; c++)if (d[c].id === a)return d[c]
      }
      return null
    };
    n.getSelectedPoints = function () {
      var a = [];
      q(R, function (b) {
        a = a.concat(wc(b.points, function (a) {
          return a.selected
        }))
      });
      return a
    };
    n.getSelectedSeries = function () {
      return wc(R, function (a) {
        return a.selected
      })
    };
    n.hideLoading = function () {
      na && ic(na, {opacity:0}, {duration:s.loading.hideDuration || 100, complete:function () {
        W(na, {display:Ka})
      }});
      jb = !1
    };
    n.initSeries = f;
    n.isInsidePlot = Ya;
    n.redraw = h;
    n.setSize = mb;
    n.setTitle =
      i;
    n.showLoading = function (a) {
      var b = s.loading;
      na || (na = da(sb, {className:gb + "loading"}, G(b.style, {left:B + la, top:U + la, width:Aa + la, height:Ba + la, zIndex:10, display:Ka}), H), Va = da("span", null, b.labelStyle, na));
      Va.innerHTML = a || s.lang.loading;
      jb || (W(na, {opacity:0, display:""}), ic(na, {opacity:b.style.opacity}, {duration:b.showDuration || 0}), jb = !0)
    };
    n.pointCount = 0;
    n.counters = new Ec;
    v()
  }

  var D, S = document, ba = window, va = Math, x = va.round, La = va.floor, gc = va.ceil, O = va.max, wa = va.min, Ga = va.abs, Na = va.cos, sa = va.sin, kb = va.PI, Nc =
    kb * 2 / 360, lb = navigator.userAgent, Ub = /msie/i.test(lb) && !ba.opera, Wb = S.documentMode === 8, Oc = /AppleWebKit/.test(lb), Kc = /Firefox/.test(lb), Tb = !!S.createElementNS && !!S.createElementNS("http://www.w3.org/2000/svg", "svg").createSVGRect, bd = Kc && parseInt(lb.split("Firefox/")[1], 10) < 4, rb = !Tb && !Ub && !!S.createElement("canvas").getContext, Sb, Fa = S.documentElement.ontouchstart !== D, Pc = {}, uc = 0, dc, ja, Bb, Vb, Xb, K, sb = "div", Db = "absolute", vc = "relative", Xa = "hidden", gb = "highcharts-", $a = "visible", la = "px", Ka = "none", ya = "M", ka =
    "L", Qc = "rgba(192,192,192," + (Tb ? 1.0E-6 : 0.0020) + ")", ra = "", fb = "hover", Hb = "millisecond", ob = "second", cb = "minute", db = "hour", P = "day", Ca = "week", pa = "month", fa = "year", cc, oc, pc, rc, eb, ac, bc, Ac, Bc, qc, Cc, Dc, w = ba.HighchartsAdapter, V = w || {}, Rc = V.getScript, q = V.each, wc = V.grep, Ic = V.offset, Kb = V.map, I = V.merge, X = V.addEvent, ua = V.removeEvent, aa = V.fireEvent, ic = V.animate, Rb = V.stop, ma = {};
  ba.Highcharts = {};
  Bb = function (a, b, c) {
    if (!A(b) || isNaN(b))return"Invalid date";
    var a = r(a, "%Y-%m-%d %H:%M:%S"), d = new Date(b), e, f = d[pc](), g = d[rc](),
      h = d[eb](), j = d[ac](), k = d[bc](), i = ja.lang, m = i.weekdays, b = {a:m[g].substr(0, 3), A:m[g], d:nb(h), e:h, b:i.shortMonths[j], B:i.months[j], m:nb(j + 1), y:k.toString().substr(2, 2), Y:k, H:nb(f), I:nb(f % 12 || 12), l:f % 12 || 12, M:nb(d[oc]()), p:f < 12 ? "AM" : "PM", P:f < 12 ? "am" : "pm", S:nb(d.getSeconds()), L:nb(x(b % 1E3), 3)};
    for (e in b)a = a.replace("%" + e, b[e]);
    return c ? a.substr(0, 1).toUpperCase() + a.substr(1) : a
  };
  Ec.prototype = {wrapColor:function (a) {
    if (this.color >= a)this.color = 0
  }, wrapSymbol:function (a) {
    if (this.symbol >= a)this.symbol = 0
  }};
  K =
    Ja(Hb, 1, ob, 1E3, cb, 6E4, db, 36E5, P, 864E5, Ca, 6048E5, pa, 2592E6, fa, 31556952E3);
  Xb = {init:function (a, b, c) {
    var b = b || "", d = a.shift, e = b.indexOf("C") > -1, f = e ? 7 : 3, g, b = b.split(" "), c = [].concat(c), h, j, k = function (a) {
      for (g = a.length; g--;)a[g] === ya && a.splice(g + 1, 0, a[g + 1], a[g + 2], a[g + 1], a[g + 2])
    };
    e && (k(b), k(c));
    a.isArea && (h = b.splice(b.length - 6, 6), j = c.splice(c.length - 6, 6));
    d === 1 && (c = [].concat(c).splice(0, f).concat(c));
    a.shift = 0;
    if (b.length)for (a = c.length; b.length < a;)d = [].concat(b).splice(b.length - f, f), e && (d[f - 6] = d[f - 2], d[f -
      5] = d[f - 1]), b = b.concat(d);
    h && (b = b.concat(h), c = c.concat(j));
    return[b, c]
  }, step:function (a, b, c, d) {
    var e = [], f = a.length;
    if (c === 1)e = d; else if (f === b.length && c < 1)for (; f--;)d = parseFloat(a[f]), e[f] = isNaN(d) ? a[f] : c * parseFloat(b[f] - d) + d; else e = b;
    return e
  }};
  w && w.init && w.init(Xb);
  if (!w && ba.jQuery) {
    var ta = jQuery, Rc = ta.getScript, q = function (a, b) {
        for (var c = 0, d = a.length; c < d; c++)if (b.call(a[c], a[c], c, a) === !1)return c
      }, wc = ta.grep, Kb = function (a, b) {
        for (var c = [], d = 0, e = a.length; d < e; d++)c[d] = b.call(a[d], a[d], d, a);
        return c
      },
      I = function () {
        var a = arguments;
        return ta.extend(!0, null, a[0], a[1], a[2], a[3])
      }, Ic = function (a) {
        return ta(a).offset()
      }, X = function (a, b, c) {
        ta(a).bind(b, c)
      }, ua = function (a, b, c) {
        var d = S.removeEventListener ? "removeEventListener" : "detachEvent";
        S[d] && !a[d] && (a[d] = function () {
        });
        ta(a).unbind(b, c)
      }, aa = function (a, b, c, d) {
        var e = ta.Event(b), f = "detached" + b, g;
        G(e, c);
        a[b] && (a[f] = a[b], a[b] = null);
        q(["preventDefault", "stopPropagation"], function (a) {
          var b = e[a];
          e[a] = function () {
            try {
              b.call(e)
            } catch (c) {
              a === "preventDefault" && (g =
                !0)
            }
          }
        });
        ta(a).trigger(e);
        a[f] && (a[b] = a[f], a[f] = null);
        d && !e.isDefaultPrevented() && !g && d(e)
      }, ic = function (a, b, c) {
        var d = ta(a);
        if (b.d)a.toD = b.d, b.d = 1;
        d.stop();
        d.animate(b, c)
      }, Rb = function (a) {
        ta(a).stop()
      };
    ta.extend(ta.easing, {easeOutQuad:function (a, b, c, d, e) {
      return-d * (b /= e) * (b - 2) + c
    }});
    var Sc = jQuery.fx, Tc = Sc.step;
    q(["cur", "_default", "width", "height"], function (a, b) {
      var c = b ? Tc : Sc.prototype, d = c[a], e;
      d && (c[a] = function (a) {
        a = b ? a : this;
        e = a.elem;
        return e.attr ? e.attr(a.prop, a.now) : d.apply(this, arguments)
      })
    });
    Tc.d =
      function (a) {
        var b = a.elem;
        if (!a.started) {
          var c = Xb.init(b, b.d, b.toD);
          a.start = c[0];
          a.end = c[1];
          a.started = !0
        }
        b.attr("d", Xb.step(a.start, a.end, a.pos, b.toD))
      }
  }
  w = {enabled:!0, align:"center", x:0, y:15, style:{color:"#666", fontSize:"11px", lineHeight:"14px"}};
  ja = {colors:"#4572A7,#AA4643,#89A54E,#80699B,#3D96AE,#DB843D,#92A8CD,#A47D7C,#B5CA92".split(","), symbols:["circle", "diamond", "square", "triangle", "triangle-down"], lang:{loading:"Loading...", months:"January,February,March,April,May,June,July,August,September,October,November,December".split(","),
    shortMonths:"Jan,Feb,Mar,Apr,May,Jun,Jul,Aug,Sep,Oct,Nov,Dec".split(","), weekdays:"Sunday,Monday,Tuesday,Wednesday,Thursday,Friday,Saturday".split(","), decimalPoint:".", resetZoom:"Reset zoom", resetZoomTitle:"Reset zoom level 1:1", thousandsSep:","}, global:{useUTC:!0, canvasToolsURL:"http://code.highcharts.com/stock/1.1.5/modules/canvas-tools.js"}, chart:{borderColor:"#4572A7", borderRadius:5, defaultSeriesType:"line", ignoreHiddenSeries:!0, spacingTop:10, spacingRight:10, spacingBottom:15, spacingLeft:10, style:{fontFamily:'"Lucida Grande", "Lucida Sans Unicode", Verdana, Arial, Helvetica, sans-serif',
    fontSize:"12px"}, backgroundColor:"#FFFFFF", plotBorderColor:"#C0C0C0", resetZoomButton:{theme:{zIndex:20}, position:{align:"right", x:-10, y:10}}}, title:{text:"Chart title", align:"center", y:15, style:{color:"#3E576F", fontSize:"16px"}}, subtitle:{text:"", align:"center", y:30, style:{color:"#6D869F"}}, plotOptions:{line:{allowPointSelect:!1, showCheckbox:!1, animation:{duration:1E3}, events:{}, lineWidth:2, shadow:!0, marker:{enabled:!0, lineWidth:0, radius:4, lineColor:"#FFFFFF", states:{hover:{}, select:{fillColor:"#FFFFFF",
    lineColor:"#000000", lineWidth:2}}}, point:{events:{}}, dataLabels:I(w, {enabled:!1, y:-6, formatter:function () {
    return this.y
  }}), cropThreshold:300, pointRange:0, showInLegend:!0, states:{hover:{marker:{}}, select:{marker:{}}}, stickyTracking:!0}}, labels:{style:{position:Db, color:"#3E576F"}}, legend:{enabled:!0, align:"center", layout:"horizontal", labelFormatter:function () {
    return this.name
  }, borderWidth:1, borderColor:"#909090", borderRadius:5, shadow:!1, style:{padding:"5px"}, itemStyle:{cursor:"pointer", color:"#3E576F"},
    itemHoverStyle:{color:"#000000"}, itemHiddenStyle:{color:"#C0C0C0"}, itemCheckboxStyle:{position:Db, width:"13px", height:"13px"}, symbolWidth:16, symbolPadding:5, verticalAlign:"bottom", x:0, y:0}, loading:{labelStyle:{fontWeight:"bold", position:vc, top:"1em"}, style:{position:Db, backgroundColor:"white", opacity:0.5, textAlign:"center"}}, tooltip:{enabled:!0, backgroundColor:"rgba(255, 255, 255, .85)", borderWidth:2, borderRadius:5, headerFormat:'<span style="font-size: 10px">{point.key}</span><br/>', pointFormat:'<span style="color:{series.color}">{series.name}</span>: <b>{point.y}</b><br/>',
    shadow:!0, shared:rb, snap:Fa ? 25 : 10, style:{color:"#333333", fontSize:"12px", padding:"5px", whiteSpace:"nowrap"}}, credits:{enabled:!0, text:"Highcharts.com", href:"http://www.highcharts.com", position:{align:"right", x:-10, verticalAlign:"bottom", y:-5}, style:{cursor:"pointer", color:"#909090", fontSize:"10px"}}};
  var hc = {dateTimeLabelFormats:Ja(Hb, "%H:%M:%S.%L", ob, "%H:%M:%S", cb, "%H:%M", db, "%H:%M", P, "%e. %b", Ca, "%e. %b", pa, "%b '%y", fa, "%Y"), endOnTick:!1, gridLineColor:"#C0C0C0", labels:w, lineColor:"#C0D0E0", lineWidth:1,
    max:null, min:null, minPadding:0.01, maxPadding:0.01, minorGridLineColor:"#E0E0E0", minorGridLineWidth:1, minorTickColor:"#A0A0A0", minorTickLength:2, minorTickPosition:"outside", startOfWeek:1, startOnTick:!1, tickColor:"#C0D0E0", tickLength:5, tickmarkPlacement:"between", tickPixelInterval:100, tickPosition:"outside", tickWidth:1, title:{align:"middle", style:{color:"#6D869F", fontWeight:"bold"}}, type:"linear"}, tc = I(hc, {endOnTick:!0, gridLineWidth:1, tickPixelInterval:72, showLastLabel:!0, labels:{align:"right", x:-8,
    y:3}, lineWidth:0, maxPadding:0.05, minPadding:0.05, startOnTick:!0, tickWidth:0, title:{rotation:270, text:"Y-values"}, stackLabels:{enabled:!1, formatter:function () {
    return this.total
  }, style:w.style}}), ad = {labels:{align:"right", x:-8, y:null}, title:{rotation:270}}, $c = {labels:{align:"left", x:8, y:null}, title:{rotation:90}}, Hc = {labels:{align:"center", x:0, y:14, overflow:"justify"}, title:{rotation:0}}, Zc = I(Hc, {labels:{y:-5, overflow:"justify"}}), J = ja.plotOptions, w = J.line;
  J.spline = I(w);
  J.scatter = I(w, {lineWidth:0, states:{hover:{lineWidth:0}},
    tooltip:{headerFormat:'<span style="font-size: 10px; color:{series.color}">{series.name}</span><br/>', pointFormat:"x: <b>{point.x}</b><br/>y: <b>{point.y}</b><br/>"}});
  J.area = I(w, {threshold:0});
  J.areaspline = I(J.area);
  J.column = I(w, {borderColor:"#FFFFFF", borderWidth:1, borderRadius:0, groupPadding:0.2, marker:null, pointPadding:0.1, minPointLength:0, cropThreshold:50, pointRange:null, states:{hover:{brightness:0.1, shadow:!1}, select:{color:"#C0C0C0", borderColor:"#000000", shadow:!1}}, dataLabels:{y:null, verticalAlign:null},
    threshold:0});
  J.bar = I(J.column, {dataLabels:{align:"left", x:5, y:null, verticalAlign:"middle"}});
  J.pie = I(w, {borderColor:"#FFFFFF", borderWidth:1, center:["50%", "50%"], colorByPoint:!0, dataLabels:{distance:30, enabled:!0, formatter:function () {
    return this.point.name
  }, y:5}, legendType:"point", marker:null, size:"75%", showInLegend:!1, slicedOffset:10, states:{hover:{brightness:0.1, shadow:!1}}});
  Gc();
  var oa = function (a) {
    var b = [], c;
    (function (a) {
      (c = /rgba\(\s*([0-9]{1,3})\s*,\s*([0-9]{1,3})\s*,\s*([0-9]{1,3})\s*,\s*([0-9]?(?:\.[0-9]+)?)\s*\)/.exec(a)) ?
        b = [Z(c[1]), Z(c[2]), Z(c[3]), parseFloat(c[4], 10)] : (c = /#([a-fA-F0-9]{2})([a-fA-F0-9]{2})([a-fA-F0-9]{2})/.exec(a)) && (b = [Z(c[1], 16), Z(c[2], 16), Z(c[3], 16), 1])
    })(a);
    return{get:function (c) {
      return b && !isNaN(b[0]) ? c === "rgb" ? "rgb(" + b[0] + "," + b[1] + "," + b[2] + ")" : c === "a" ? b[3] : "rgba(" + b.join(",") + ")" : a
    }, brighten:function (a) {
      if (Yb(a) && a !== 0) {
        var c;
        for (c = 0; c < 3; c++)b[c] += Z(a * 255), b[c] < 0 && (b[c] = 0), b[c] > 255 && (b[c] = 255)
      }
      return this
    }, setOpacity:function (a) {
      b[3] = a;
      return this
    }}
  };
  Qa.prototype = {init:function (a, b) {
    this.element =
      b === "span" ? da(b) : S.createElementNS("http://www.w3.org/2000/svg", b);
    this.renderer = a;
    this.attrSetters = {}
  }, animate:function (a, b, c) {
    b = r(b, Vb, !0);
    Rb(this);
    if (b) {
      b = I(b);
      if (c)b.complete = c;
      ic(this, a, b)
    } else this.attr(a), c && c()
  }, attr:function (a, b) {
    var c, d, e, f, g = this.element, h = g.nodeName, j = this.renderer, k, i = this.attrSetters, m = this.shadows, l, o = this;
    Gb(a) && A(b) && (c = a, a = {}, a[c] = b);
    if (Gb(a))c = a, h === "circle" ? c = {x:"cx", y:"cy"}[c] || c : c === "strokeWidth" && (c = "stroke-width"), o = $(g, c) || this[c] || 0, c !== "d" && c !== "visibility" &&
      (o = parseFloat(o)); else for (c in a)if (k = !1, d = a[c], e = i[c] && i[c](d, c), e !== !1) {
      e !== D && (d = e);
      if (c === "d")d && d.join && (d = d.join(" ")), /(NaN| {2}|^$)/.test(d) && (d = "M 0 0"), this.d = d; else if (c === "x" && h === "text") {
        for (e = 0; e < g.childNodes.length; e++)f = g.childNodes[e], $(f, "x") === $(g, "x") && $(f, "x", d);
        this.rotation && $(g, "transform", "rotate(" + this.rotation + " " + d + " " + Z(a.y || $(g, "y")) + ")")
      } else if (c === "fill")d = j.color(d, g, c); else if (h === "circle" && (c === "x" || c === "y"))c = {x:"cx", y:"cy"}[c] || c; else if (h === "rect" && c === "r")$(g,
        {rx:d, ry:d}), k = !0; else if (c === "translateX" || c === "translateY" || c === "rotation" || c === "verticalAlign")this[c] = d, this.updateTransform(), k = !0; else if (c === "stroke")d = j.color(d, g, c); else if (c === "dashstyle")if (c = "stroke-dasharray", d = d && d.toLowerCase(), d === "solid")d = Ka; else {
        if (d) {
          d = d.replace("shortdashdotdot", "3,1,1,1,1,1,").replace("shortdashdot", "3,1,1,1").replace("shortdot", "1,1,").replace("shortdash", "3,1,").replace("longdash", "8,3,").replace(/dot/g, "1,3,").replace("dash", "4,3,").replace(/,$/, "").split(",");
          for (e = d.length; e--;)d[e] = Z(d[e]) * a["stroke-width"];
          d = d.join(",")
        }
      } else c === "isTracker" ? this[c] = d : c === "width" ? d = Z(d) : c === "align" ? (c = "text-anchor", d = {left:"start", center:"middle", right:"end"}[d]) : c === "title" && (e = S.createElementNS("http://www.w3.org/2000/svg", "title"), e.appendChild(S.createTextNode(d)), g.appendChild(e));
      c === "strokeWidth" && (c = "stroke-width");
      Oc && c === "stroke-width" && d === 0 && (d = 1.0E-6);
      this.symbolName && /^(x|y|r|start|end|innerR|anchorX|anchorY)/.test(c) && (l || (this.symbolAttr(a), l = !0), k =
        !0);
      if (m && /^(width|height|visibility|x|y|d|transform)$/.test(c))for (e = m.length; e--;)$(m[e], c, d);
      if ((c === "width" || c === "height") && h === "rect" && d < 0)d = 0;
      c === "text" ? (this.textStr = d, this.added && j.buildText(this)) : k || $(g, c, d)
    }
    if (Oc && /Chrome\/(18|19)/.test(lb) && h === "text" && (a.x !== D || a.y !== D))c = g.parentNode, d = g.nextSibling, c && (c.removeChild(g), d ? c.insertBefore(g, d) : c.appendChild(g));
    return o
  }, symbolAttr:function (a) {
    var b = this;
    q("x,y,r,start,end,width,height,innerR,anchorX,anchorY".split(","), function (c) {
      b[c] =
        r(a[c], b[c])
    });
    b.attr({d:b.renderer.symbols[b.symbolName](b.x, b.y, b.width, b.height, b)})
  }, clip:function (a) {
    return this.attr("clip-path", "url(" + this.renderer.url + "#" + a.id + ")")
  }, crisp:function (a, b, c, d, e) {
    var f, g = {}, h = {}, j, a = a || this.strokeWidth || this.attr && this.attr("stroke-width") || 0;
    j = x(a) % 2 / 2;
    h.x = La(b || this.x || 0) + j;
    h.y = La(c || this.y || 0) + j;
    h.width = La((d || this.width || 0) - 2 * j);
    h.height = La((e || this.height || 0) - 2 * j);
    h.strokeWidth = a;
    for (f in h)this[f] !== h[f] && (this[f] = g[f] = h[f]);
    return g
  }, css:function (a) {
    var b =
      this.element, b = a && a.width && b.nodeName === "text", c, d = "", e = function (a, b) {
      return"-" + b.toLowerCase()
    };
    if (a && a.color)a.fill = a.color;
    this.styles = a = G(this.styles, a);
    if (Ub && !Tb)b && delete a.width, W(this.element, a); else {
      for (c in a)d += c.replace(/([A-Z])/g, e) + ":" + a[c] + ";";
      this.attr({style:d})
    }
    b && this.added && this.renderer.buildText(this);
    return this
  }, on:function (a, b) {
    var c = b;
    Fa && a === "click" && (a = "touchstart", c = function (a) {
      a.preventDefault();
      b()
    });
    this.element["on" + a] = c;
    return this
  }, translate:function (a, b) {
    return this.attr({translateX:a,
      translateY:b})
  }, invert:function () {
    this.inverted = !0;
    this.updateTransform();
    return this
  }, htmlCss:function (a) {
    var b = this.element;
    if (b = a && b.tagName === "SPAN" && a.width)delete a.width, this.textWidth = b, this.updateTransform();
    this.styles = G(this.styles, a);
    W(this.element, a);
    return this
  }, htmlGetBBox:function (a) {
    var b = this.element, c = this.bBox;
    if (!c || a) {
      if (b.nodeName === "text")b.style.position = Db;
      c = this.bBox = {x:b.offsetLeft, y:b.offsetTop, width:b.offsetWidth, height:b.offsetHeight}
    }
    return c
  }, htmlUpdateTransform:function () {
    if (this.added) {
      var a =
        this.renderer, b = this.element, c = this.translateX || 0, d = this.translateY || 0, e = this.x || 0, f = this.y || 0, g = this.textAlign || "left", h = {left:0, center:0.5, right:1}[g], j = g && g !== "left", k = this.shadows;
      if (c || d)W(b, {marginLeft:c, marginTop:d}), k && q(k, function (a) {
        W(a, {marginLeft:c + 1, marginTop:d + 1})
      });
      this.inverted && q(b.childNodes, function (c) {
        a.invertChild(c, b)
      });
      if (b.tagName === "SPAN") {
        var i, m, k = this.rotation, l;
        i = 0;
        var o = 1, t = 0, u;
        l = Z(this.textWidth);
        var v = this.xCorr || 0, s = this.yCorr || 0, Y = [k, g, b.innerHTML, this.textWidth].join(",");
        if (Y !== this.cTT)A(k) && (i = k * Nc, o = Na(i), t = sa(i), W(b, {filter:k ? ["progid:DXImageTransform.Microsoft.Matrix(M11=", o, ", M12=", -t, ", M21=", t, ", M22=", o, ", sizingMethod='auto expand')"].join("") : Ka})), i = r(this.elemWidth, b.offsetWidth), m = r(this.elemHeight, b.offsetHeight), i > l && (W(b, {width:l + la, display:"block", whiteSpace:"normal"}), i = l), l = a.fontMetrics(b.style.fontSize).b, v = o < 0 && -i, s = t < 0 && -m, u = o * t < 0, v += t * l * (u ? 1 - h : h), s -= o * l * (k ? u ? h : 1 - h : 1), j && (v -= i * h * (o < 0 ? -1 : 1), k && (s -= m * h * (t < 0 ? -1 : 1)), W(b, {textAlign:g})), this.xCorr =
          v, this.yCorr = s;
        W(b, {left:e + v + la, top:f + s + la});
        this.cTT = Y
      }
    } else this.alignOnAdd = !0
  }, updateTransform:function () {
    var a = this.translateX || 0, b = this.translateY || 0, c = this.inverted, d = this.rotation, e = [];
    c && (a += this.attr("width"), b += this.attr("height"));
    (a || b) && e.push("translate(" + a + "," + b + ")");
    c ? e.push("rotate(90) scale(-1,1)") : d && e.push("rotate(" + d + " " + this.x + " " + this.y + ")");
    e.length && $(this.element, "transform", e.join(" "))
  }, toFront:function () {
    var a = this.element;
    a.parentNode.appendChild(a);
    return this
  }, align:function (a, b, c) {
    a ? (this.alignOptions = a, this.alignByTranslate = b, c || this.renderer.alignedObjects.push(this)) : (a = this.alignOptions, b = this.alignByTranslate);
    var c = r(c, this.renderer), d = a.align, e = a.verticalAlign, f = (c.x || 0) + (a.x || 0), g = (c.y || 0) + (a.y || 0), h = {};
    /^(right|center)$/.test(d) && (f += (c.width - (a.width || 0)) / {right:1, center:2}[d]);
    h[b ? "translateX" : "x"] = x(f);
    /^(bottom|middle)$/.test(e) && (g += (c.height - (a.height || 0)) / ({bottom:1, middle:2}[e] || 1));
    h[b ? "translateY" : "y"] = x(g);
    this[this.placed ? "animate" : "attr"](h);
    this.placed =
      !0;
    this.alignAttr = h;
    return this
  }, getBBox:function (a) {
    var b, c, d = this.rotation;
    c = this.element;
    var e = d * Nc;
    if (c.namespaceURI === "http://www.w3.org/2000/svg") {
      try {
        b = c.getBBox ? G({}, c.getBBox()) : {width:c.offsetWidth, height:c.offsetHeight}
      } catch (f) {
      }
      if (!b || b.width < 0)b = {width:0, height:0};
      a = b.width;
      c = b.height;
      if (d)b.width = Ga(c * sa(e)) + Ga(a * Na(e)), b.height = Ga(c * Na(e)) + Ga(a * sa(e))
    } else b = this.htmlGetBBox(a);
    return b
  }, show:function () {
    return this.attr({visibility:$a})
  }, hide:function () {
    return this.attr({visibility:Xa})
  },
    add:function (a) {
      var b = this.renderer, c = a || b, d = c.element || b.box, e = d.childNodes, f = this.element, g = $(f, "zIndex"), h;
      this.parentInverted = a && a.inverted;
      this.textStr !== void 0 && b.buildText(this);
      if (g)c.handleZ = !0, g = Z(g);
      if (c.handleZ)for (c = 0; c < e.length; c++)if (a = e[c], b = $(a, "zIndex"), a !== f && (Z(b) > g || !A(g) && A(b))) {
        d.insertBefore(f, a);
        h = !0;
        break
      }
      h || d.appendChild(f);
      this.added = !0;
      aa(this, "add");
      return this
    }, safeRemoveChild:function (a) {
      var b = a.parentNode;
      b && b.removeChild(a)
    }, destroy:function () {
      var a = this, b = a.element ||
      {}, c = a.shadows, d = a.box, e, f;
      b.onclick = b.onmouseout = b.onmouseover = b.onmousemove = null;
      Rb(a);
      if (a.clipPath)a.clipPath = a.clipPath.destroy();
      if (a.stops) {
        for (f = 0; f < a.stops.length; f++)a.stops[f] = a.stops[f].destroy();
        a.stops = null
      }
      a.safeRemoveChild(b);
      c && q(c, function (b) {
        a.safeRemoveChild(b)
      });
      d && d.destroy();
      Lb(a.renderer.alignedObjects, a);
      for (e in a)delete a[e];
      return null
    }, empty:function () {
      for (var a = this.element, b = a.childNodes, c = b.length; c--;)a.removeChild(b[c])
    }, shadow:function (a, b) {
      var c = [], d, e, f = this.element,
        g = this.parentInverted ? "(-1,-1)" : "(1,1)";
      if (a) {
        for (d = 1; d <= 3; d++)e = f.cloneNode(0), $(e, {isShadow:"true", stroke:"rgb(0, 0, 0)", "stroke-opacity":0.05 * d, "stroke-width":7 - 2 * d, transform:"translate" + g, fill:Ka}), b ? b.element.appendChild(e) : f.parentNode.insertBefore(e, f), c.push(e);
        this.shadows = c
      }
      return this
    }};
  var Eb = function () {
    this.init.apply(this, arguments)
  };
  Eb.prototype = {Element:Qa, init:function (a, b, c, d) {
    var e = location, f;
    f = this.createElement("svg").attr({xmlns:"http://www.w3.org/2000/svg", version:"1.1"});
    a.appendChild(f.element);
    this.isSVG = !0;
    this.box = f.element;
    this.boxWrapper = f;
    this.alignedObjects = [];
    this.url = Ub ? "" : e.href.replace(/#.*?$/, "").replace(/([\('\)])/g, "\\$1");
    this.defs = this.createElement("defs").add();
    this.forExport = d;
    this.gradients = {};
    this.setSize(b, c, !1)
  }, destroy:function () {
    var a = this.defs;
    this.box = null;
    this.boxWrapper = this.boxWrapper.destroy();
    Ab(this.gradients || {});
    this.gradients = null;
    if (a)this.defs = a.destroy();
    return this.alignedObjects = null
  }, createElement:function (a) {
    var b = new this.Element;
    b.init(this, a);
    return b
  }, draw:function () {
  }, buildText:function (a) {
    for (var b = a.element, c = r(a.textStr, "").toString().replace(/<(b|strong)>/g, '<span style="font-weight:bold">').replace(/<(i|em)>/g, '<span style="font-style:italic">').replace(/<a/g, "<span").replace(/<\/(b|strong|i|em|a)>/g, "</span>").split(/<br.*?>/g), d = b.childNodes, e = /style="([^"]+)"/, f = /href="([^"]+)"/, g = $(b, "x"), h = a.styles, j = h && Z(h.width), k = h && h.lineHeight, i, h = d.length; h--;)b.removeChild(d[h]);
    j && !a.added && this.box.appendChild(b);
    c[c.length - 1] === "" &&
    c.pop();
    q(c, function (c, d) {
      var h, t = 0, u, c = c.replace(/<span/g, "|||<span").replace(/<\/span>/g, "</span>|||");
      h = c.split("|||");
      q(h, function (c) {
        if (c !== "" || h.length === 1) {
          var m = {}, q = S.createElementNS("http://www.w3.org/2000/svg", "tspan");
          e.test(c) && $(q, "style", c.match(e)[1].replace(/(;| |^)color([ :])/, "$1fill$2"));
          f.test(c) && ($(q, "onclick", 'location.href="' + c.match(f)[1] + '"'), W(q, {cursor:"pointer"}));
          c = (c.replace(/<(.|\n)*?>/g, "") || " ").replace(/&lt;/g, "<").replace(/&gt;/g, ">");
          q.appendChild(S.createTextNode(c));
          t ? m.dx = 3 : m.x = g;
          if (!t) {
            if (d) {
              !Tb && a.renderer.forExport && W(q, {display:"block"});
              u = ba.getComputedStyle && Z(ba.getComputedStyle(i, null).getPropertyValue("line-height"));
              if (!u || isNaN(u))u = k || i.offsetHeight || 18;
              $(q, "dy", u)
            }
            i = q
          }
          $(q, m);
          b.appendChild(q);
          t++;
          if (j)for (var c = c.replace(/-/g, "- ").split(" "), p, r = []; c.length || r.length;)p = a.getBBox().width, m = p > j, !m || c.length === 1 ? (c = r, r = [], c.length && (q = S.createElementNS("http://www.w3.org/2000/svg", "tspan"), $(q, {dy:k || 16, x:g}), b.appendChild(q), p > j && (j = p))) : (q.removeChild(q.firstChild),
            r.unshift(c.pop())), c.length && q.appendChild(S.createTextNode(c.join(" ").replace(/- /g, "-")))
        }
      })
    })
  }, button:function (a, b, c, d, e, f, g) {
    var h = this.label(a, b, c), j = 0, k, i, m, l, o, a = {x1:0, y1:0, x2:0, y2:1}, e = I(Ja("stroke-width", 1, "stroke", "#999", "fill", Ja("linearGradient", a, "stops", [
      [0, "#FFF"],
      [1, "#DDD"]
    ]), "r", 3, "padding", 3, "style", Ja("color", "black")), e);
    m = e.style;
    delete e.style;
    f = I(e, Ja("stroke", "#68A", "fill", Ja("linearGradient", a, "stops", [
      [0, "#FFF"],
      [1, "#ACF"]
    ])), f);
    l = f.style;
    delete f.style;
    g = I(e, Ja("stroke",
      "#68A", "fill", Ja("linearGradient", a, "stops", [
        [0, "#9BD"],
        [1, "#CDF"]
      ])), g);
    o = g.style;
    delete g.style;
    X(h.element, "mouseenter", function () {
      h.attr(f).css(l)
    });
    X(h.element, "mouseleave", function () {
      k = [e, f, g][j];
      i = [m, l, o][j];
      h.attr(k).css(i)
    });
    h.setState = function (a) {
      (j = a) ? a === 2 && h.attr(g).css(o) : h.attr(e).css(m)
    };
    return h.on("click",function () {
      d.call(h)
    }).attr(e).css(G({cursor:"default"}, m))
  }, crispLine:function (a, b) {
    a[1] === a[4] && (a[1] = a[4] = x(a[1]) + b % 2 / 2);
    a[2] === a[5] && (a[2] = a[5] = x(a[2]) + b % 2 / 2);
    return a
  }, path:function (a) {
    return this.createElement("path").attr({d:a,
      fill:Ka})
  }, circle:function (a, b, c) {
    a = xb(a) ? a : {x:a, y:b, r:c};
    return this.createElement("circle").attr(a)
  }, arc:function (a, b, c, d, e, f) {
    if (xb(a))b = a.y, c = a.r, d = a.innerR, e = a.start, f = a.end, a = a.x;
    return this.symbol("arc", a || 0, b || 0, c || 0, c || 0, {innerR:d || 0, start:e || 0, end:f || 0})
  }, rect:function (a, b, c, d, e, f) {
    if (xb(a))b = a.y, c = a.width, d = a.height, e = a.r, f = a.strokeWidth, a = a.x;
    e = this.createElement("rect").attr({rx:e, ry:e, fill:Ka});
    return e.attr(e.crisp(f, a, b, O(c, 0), O(d, 0)))
  }, setSize:function (a, b, c) {
    var d = this.alignedObjects,
      e = d.length;
    this.width = a;
    this.height = b;
    for (this.boxWrapper[r(c, !0) ? "animate" : "attr"]({width:a, height:b}); e--;)d[e].align()
  }, g:function (a) {
    var b = this.createElement("g");
    return A(a) ? b.attr({"class":gb + a}) : b
  }, image:function (a, b, c, d, e) {
    var f = {preserveAspectRatio:Ka};
    arguments.length > 1 && G(f, {x:b, y:c, width:d, height:e});
    f = this.createElement("image").attr(f);
    f.element.setAttributeNS ? f.element.setAttributeNS("http://www.w3.org/1999/xlink", "href", a) : f.element.setAttribute("hc-svg-href", a);
    return f
  }, symbol:function (a, b, c, d, e, f) {
    var g, h = this.symbols[a], h = h && h(x(b), x(c), d, e, f), j = /^url\((.*?)\)$/, k;
    if (h)g = this.path(h), G(g, {symbolName:a, x:b, y:c, width:d, height:e}), f && G(g, f); else if (j.test(a)) {
      var i = function (a, b) {
        a.attr({width:b[0], height:b[1]}).translate(-x(b[0] / 2), -x(b[1] / 2))
      };
      k = a.match(j)[1];
      a = Pc[k];
      g = this.image(k).attr({x:b, y:c});
      a ? i(g, a) : (g.attr({width:0, height:0}), da("img", {onload:function () {
        i(g, Pc[k] = [this.width, this.height])
      }, src:k}))
    }
    return g
  }, symbols:{circle:function (a, b, c, d) {
    var e = 0.166 * c;
    return[ya, a + c / 2,
      b, "C", a + c + e, b, a + c + e, b + d, a + c / 2, b + d, "C", a - e, b + d, a - e, b, a + c / 2, b, "Z"]
  }, square:function (a, b, c, d) {
    return[ya, a, b, ka, a + c, b, a + c, b + d, a, b + d, "Z"]
  }, triangle:function (a, b, c, d) {
    return[ya, a + c / 2, b, ka, a + c, b + d, a, b + d, "Z"]
  }, "triangle-down":function (a, b, c, d) {
    return[ya, a, b, ka, a + c, b, a + c / 2, b + d, "Z"]
  }, diamond:function (a, b, c, d) {
    return[ya, a + c / 2, b, ka, a + c, b + d / 2, a + c / 2, b + d, a, b + d / 2, "Z"]
  }, arc:function (a, b, c, d, e) {
    var f = e.start, c = e.r || c || d, g = e.end - 1.0E-6, d = e.innerR, h = Na(f), j = sa(f), k = Na(g), g = sa(g), e = e.end - f < kb ? 0 : 1;
    return[ya, a + c * h, b + c *
      j, "A", c, c, 0, e, 1, a + c * k, b + c * g, ka, a + d * k, b + d * g, "A", d, d, 0, e, 0, a + d * h, b + d * j, "Z"]
  }}, clipRect:function (a, b, c, d) {
    var e = gb + uc++, f = this.createElement("clipPath").attr({id:e}).add(this.defs), a = this.rect(a, b, c, d, 0).add(f);
    a.id = e;
    a.clipPath = f;
    return a
  }, color:function (a, b, c) {
    var d, e = /^rgba/;
    if (a && a.linearGradient) {
      var f = this, g = a.linearGradient, b = !mc(g), c = f.gradients, h, j = g.x1 || g[0] || 0, k = g.y1 || g[1] || 0, i = g.x2 || g[2] || 0, m = g.y2 || g[3] || 0, l, o, t = [b, j, k, i, m, a.stops.join(",")].join(",");
      c[t] ? g = $(c[t].element, "id") : (g = gb + uc++,
        h = f.createElement("linearGradient").attr(G({id:g, x1:j, y1:k, x2:i, y2:m}, b ? null : {gradientUnits:"userSpaceOnUse"})).add(f.defs), h.stops = [], q(a.stops, function (a) {
        e.test(a[1]) ? (d = oa(a[1]), l = d.get("rgb"), o = d.get("a")) : (l = a[1], o = 1);
        a = f.createElement("stop").attr({offset:a[0], "stop-color":l, "stop-opacity":o}).add(h);
        h.stops.push(a)
      }), c[t] = h);
      return"url(" + this.url + "#" + g + ")"
    } else return e.test(a) ? (d = oa(a), $(b, c + "-opacity", d.get("a")), d.get("rgb")) : (b.removeAttribute(c + "-opacity"), a)
  }, text:function (a, b, c, d) {
    var e =
      ja.chart.style;
    if (d && !this.forExport)return this.html(a, b, c);
    b = x(r(b, 0));
    c = x(r(c, 0));
    a = this.createElement("text").attr({x:b, y:c, text:a}).css({fontFamily:e.fontFamily, fontSize:e.fontSize});
    a.x = b;
    a.y = c;
    return a
  }, html:function (a, b, c) {
    var d = ja.chart.style, e = this.createElement("span"), f = e.attrSetters, g = e.element, h = e.renderer;
    f.text = function (a) {
      g.innerHTML = a;
      return!1
    };
    f.x = f.y = f.align = function (a, b) {
      b === "align" && (b = "textAlign");
      e[b] = a;
      e.htmlUpdateTransform();
      return!1
    };
    e.attr({text:a, x:x(b), y:x(c)}).css({position:Db,
      whiteSpace:"nowrap", fontFamily:d.fontFamily, fontSize:d.fontSize});
    e.css = e.htmlCss;
    if (h.isSVG)e.add = function (a) {
      var b, c, d = h.box.parentNode;
      if (a) {
        if (b = a.div, !b)b = a.div = da(sb, {className:$(a.element, "class")}, {position:Db, left:a.attr("translateX") + la, top:a.attr("translateY") + la}, d), c = b.style, G(a.attrSetters, {translateX:function (a) {
          c.left = a + la
        }, translateY:function (a) {
          c.top = a + la
        }, visibility:function (a, b) {
          c[b] = a
        }})
      } else b = d;
      b.appendChild(g);
      e.added = !0;
      e.alignOnAdd && e.htmlUpdateTransform();
      return e
    };
    return e
  },
    fontMetrics:function (a) {
      var a = Z(a || 11), a = a < 24 ? a + 4 : x(a * 1.2), b = x(a * 0.8);
      return{h:a, b:b}
    }, label:function (a, b, c, d, e, f, g, h) {
      function j() {
        var a = l.styles, a = a && a.textAlign, b = s, c;
        c = h ? 0 : F;
        if (A(r) && (a === "center" || a === "right"))b += {center:0.5, right:1}[a] * (r - u.width);
        (b !== o.x || c !== o.y) && o.attr({x:b, y:c});
        o.x = b;
        o.y = c
      }

      function k(a, b) {
        t ? t.attr(a, b) : N[a] = b
      }

      function i() {
        l.attr({text:a, x:b, y:c, anchorX:e, anchorY:f})
      }

      var m = this, l = m.g(), o = m.text("", 0, 0, g).attr({zIndex:1}).add(l), t, u, v = "left", s = 3, r, p, qa, M, w = 0, N = {}, F, g = l.attrSetters;
      X(l, "add", i);
      g.width = function (a) {
        r = a;
        return!1
      };
      g.height = function (a) {
        p = a;
        return!1
      };
      g.padding = function (a) {
        A(a) && a !== s && (s = a, j());
        return!1
      };
      g.align = function (a) {
        v = a;
        return!1
      };
      g.text = function (a, b) {
        o.attr(b, a);
        var c;
        c = o.element.style;
        u = (r === void 0 || p === void 0 || l.styles.textAlign) && o.getBBox(!0);
        l.width = (r || u.width) + 2 * s;
        l.height = (p || u.height) + 2 * s;
        F = s + m.fontMetrics(c && c.fontSize).b;
        if (!t)c = h ? -F : 0, l.box = t = d ? m.symbol(d, 0, c, l.width, l.height) : m.rect(0, c, l.width, l.height, 0, N["stroke-width"]), t.add(l);
        t.attr(I({width:l.width,
          height:l.height}, N));
        N = null;
        j();
        return!1
      };
      g["stroke-width"] = function (a, b) {
        w = a % 2 / 2;
        k(b, a);
        return!1
      };
      g.stroke = g.fill = g.r = function (a, b) {
        k(b, a);
        return!1
      };
      g.anchorX = function (a, b) {
        e = a;
        k(b, a + w - qa);
        return!1
      };
      g.anchorY = function (a, b) {
        f = a;
        k(b, a - M);
        return!1
      };
      g.x = function (a) {
        a -= {left:0, center:0.5, right:1}[v] * ((r || u.width) + s);
        qa = l.x = x(a);
        l.attr("translateX", qa);
        return!1
      };
      g.y = function (a) {
        M = l.y = x(a);
        l.attr("translateY", a);
        return!1
      };
      var ga = l.css;
      return G(l, {css:function (a) {
        if (a) {
          var b = {}, a = I({}, a);
          q("fontSize,fontWeight,fontFamily,color,lineHeight,width".split(","),
            function (c) {
              a[c] !== D && (b[c] = a[c], delete a[c])
            });
          o.css(b)
        }
        return ga.call(l, a)
      }, getBBox:function () {
        return t.getBBox()
      }, shadow:function (a) {
        t.shadow(a);
        return l
      }, destroy:function () {
        ua(l, "add", i);
        ua(l.element, "mouseenter");
        ua(l.element, "mouseleave");
        o && (o = o.destroy());
        Qa.prototype.destroy.call(l)
      }})
    }};
  Sb = Eb;
  var mb;
  if (!Tb && !rb)w = {init:function (a, b) {
    var c = ["<", b, ' filled="f" stroked="f"'], d = ["position: ", Db, ";"];
    (b === "shape" || b === sb) && d.push("left:0;top:0;width:10px;height:10px;");
    Wb && d.push("visibility: ",
      b === sb ? Xa : $a);
    c.push(' style="', d.join(""), '"/>');
    if (b)c = b === sb || b === "span" || b === "img" ? c.join("") : a.prepVML(c), this.element = da(c);
    this.renderer = a;
    this.attrSetters = {}
  }, add:function (a) {
    var b = this.renderer, c = this.element, d = b.box, d = a ? a.element || a : d;
    a && a.inverted && b.invertChild(c, d);
    Wb && d.gVis === Xa && W(c, {visibility:Xa});
    d.appendChild(c);
    this.added = !0;
    this.alignOnAdd && !this.deferUpdateTransform && this.updateTransform();
    aa(this, "add");
    return this
  }, toggleChildren:function (a, b) {
    for (var c = a.childNodes, d = c.length; d--;)W(c[d],
      {visibility:b}), c[d].nodeName === "DIV" && this.toggleChildren(c[d], b)
  }, updateTransform:Qa.prototype.htmlUpdateTransform, attr:function (a, b) {
    var c, d, e, f = this.element || {}, g = f.style, h = f.nodeName, j = this.renderer, k = this.symbolName, i, m = this.shadows, l, o = this.attrSetters, t = this;
    Gb(a) && A(b) && (c = a, a = {}, a[c] = b);
    if (Gb(a))c = a, t = c === "strokeWidth" || c === "stroke-width" ? this.strokeweight : this[c]; else for (c in a)if (d = a[c], l = !1, e = o[c] && o[c](d, c), e !== !1 && d !== null) {
      e !== D && (d = e);
      if (k && /^(x|y|r|start|end|width|height|innerR|anchorX|anchorY)/.test(c))i ||
        (this.symbolAttr(a), i = !0), l = !0; else if (c === "d") {
        d = d || [];
        this.d = d.join(" ");
        e = d.length;
        for (l = []; e--;)l[e] = Yb(d[e]) ? x(d[e] * 10) - 5 : d[e] === "Z" ? "x" : d[e];
        d = l.join(" ") || "x";
        f.path = d;
        if (m)for (e = m.length; e--;)m[e].path = d;
        l = !0
      } else if (c === "zIndex" || c === "visibility") {
        if (Wb && c === "visibility" && h === "DIV")f.gVis = d, this.toggleChildren(f, d), d === $a && (d = null);
        d && (g[c] = d);
        l = !0
      } else if (c === "width" || c === "height")d = O(0, d), this[c] = d, this.updateClipping ? (this[c] = d, this.updateClipping()) : g[c] = d, l = !0; else if (c === "x" || c === "y")this[c] =
        d, g[{x:"left", y:"top"}[c]] = d; else if (c === "class")f.className = d; else if (c === "stroke")d = j.color(d, f, c), c = "strokecolor"; else if (c === "stroke-width" || c === "strokeWidth")f.stroked = d ? !0 : !1, c = "strokeweight", this[c] = d, Yb(d) && (d += la); else if (c === "dashstyle")(f.getElementsByTagName("stroke")[0] || da(j.prepVML(["<stroke/>"]), null, null, f))[c] = d || "solid", this.dashstyle = d, l = !0; else if (c === "fill")h === "SPAN" ? g.color = d : (f.filled = d !== Ka ? !0 : !1, d = j.color(d, f, c), c = "fillcolor"); else if (c === "translateX" || c === "translateY" ||
        c === "rotation")this[c] = d, this.updateTransform(), l = !0; else if (c === "text")this.bBox = null, f.innerHTML = d, l = !0;
      if (m && c === "visibility")for (e = m.length; e--;)m[e].style[c] = d;
      l || (Wb ? f[c] = d : $(f, c, d))
    }
    return t
  }, clip:function (a) {
    var b = this, c = a.members;
    c.push(b);
    b.destroyClip = function () {
      Lb(c, b)
    };
    return b.css(a.getCSS(b.inverted))
  }, css:Qa.prototype.htmlCss, safeRemoveChild:function (a) {
    a.parentNode && Nb(a)
  }, destroy:function () {
    this.destroyClip && this.destroyClip();
    return Qa.prototype.destroy.apply(this)
  }, empty:function () {
    for (var a =
      this.element.childNodes, b = a.length, c; b--;)c = a[b], c.parentNode.removeChild(c)
  }, on:function (a, b) {
    this.element["on" + a] = function () {
      var a = ba.event;
      a.target = a.srcElement;
      b(a)
    };
    return this
  }, shadow:function (a, b) {
    var c = [], d, e = this.element, f = this.renderer, g, h = e.style, j, k = e.path;
    k && typeof k.value !== "string" && (k = "x");
    if (a) {
      for (d = 1; d <= 3; d++)j = ['<shape isShadow="true" strokeweight="', 7 - 2 * d, '" filled="false" path="', k, '" coordsize="100,100" style="', e.style.cssText, '" />'], g = da(f.prepVML(j), null, {left:Z(h.left) +
        1, top:Z(h.top) + 1}), j = ['<stroke color="black" opacity="', 0.05 * d, '"/>'], da(f.prepVML(j), null, null, g), b ? b.element.appendChild(g) : e.parentNode.insertBefore(g, e), c.push(g);
      this.shadows = c
    }
    return this
  }}, w = ea(Qa, w), w = {Element:w, isIE8:lb.indexOf("MSIE 8.0") > -1, init:function (a, b, c) {
    var d, e;
    this.alignedObjects = [];
    d = this.createElement(sb);
    e = d.element;
    e.style.position = vc;
    a.appendChild(d.element);
    this.box = e;
    this.boxWrapper = d;
    this.setSize(b, c, !1);
    if (!S.namespaces.hcv)S.namespaces.add("hcv", "urn:schemas-microsoft-com:vml"),
      S.createStyleSheet().cssText = "hcv\\:fill, hcv\\:path, hcv\\:shape, hcv\\:stroke{ behavior:url(#default#VML); display: inline-block; } "
  }, clipRect:function (a, b, c, d) {
    var e = this.createElement();
    return G(e, {members:[], left:a, top:b, width:c, height:d, getCSS:function (a) {
      var b = this.top, c = this.left, d = c + this.width, e = b + this.height, b = {clip:"rect(" + x(a ? c : b) + "px," + x(a ? e : d) + "px," + x(a ? d : e) + "px," + x(a ? b : c) + "px)"};
      !a && Wb && G(b, {width:d + la, height:e + la});
      return b
    }, updateClipping:function () {
      q(e.members, function (a) {
        a.css(e.getCSS(a.inverted))
      })
    }})
  },
    color:function (a, b, c) {
      var d, e = /^rgba/;
      if (a && a.linearGradient) {
        var f, g, h = a.linearGradient, j = h.x1 || h[0] || 0, k = h.y1 || h[1] || 0, i = h.x2 || h[2] || 0, h = h.y2 || h[3] || 0, m, l, o, t;
        q(a.stops, function (a, b) {
          e.test(a[1]) ? (d = oa(a[1]), f = d.get("rgb"), g = d.get("a")) : (f = a[1], g = 1);
          b ? (o = f, t = g) : (m = f, l = g)
        });
        if (c === "fill")a = 90 - va.atan((h - k) / (i - j)) * 180 / kb, a = ['<fill colors="0% ', m, ",100% ", o, '" angle="', a, '" opacity="', t, '" o:opacity2="', l, '" type="gradient" focus="100%" method="sigma" />'], da(this.prepVML(a), null, null, b); else return f
      } else if (e.test(a) &&
        b.tagName !== "IMG")return d = oa(a), a = ["<", c, ' opacity="', d.get("a"), '"/>'], da(this.prepVML(a), null, null, b), d.get("rgb"); else {
        b = b.getElementsByTagName(c);
        if (b.length)b[0].opacity = 1;
        return a
      }
    }, prepVML:function (a) {
      var b = this.isIE8, a = a.join("");
      b ? (a = a.replace("/>", ' xmlns="urn:schemas-microsoft-com:vml" />'), a = a.indexOf('style="') === -1 ? a.replace("/>", ' style="display:inline-block;behavior:url(#default#VML);" />') : a.replace('style="', 'style="display:inline-block;behavior:url(#default#VML);')) : a = a.replace("<",
        "<hcv:");
      return a
    }, text:Eb.prototype.html, path:function (a) {
      return this.createElement("shape").attr({coordsize:"100 100", d:a})
    }, circle:function (a, b, c) {
      return this.symbol("circle").attr({x:a - c, y:b - c, width:2 * c, height:2 * c})
    }, g:function (a) {
      var b;
      a && (b = {className:gb + a, "class":gb + a});
      return this.createElement(sb).attr(b)
    }, image:function (a, b, c, d, e) {
      var f = this.createElement("img").attr({src:a});
      arguments.length > 1 && f.css({left:b, top:c, width:d, height:e});
      return f
    }, rect:function (a, b, c, d, e, f) {
      if (xb(a))b = a.y, c =
        a.width, d = a.height, f = a.strokeWidth, a = a.x;
      var g = this.symbol("rect");
      g.r = e;
      return g.attr(g.crisp(f, a, b, O(c, 0), O(d, 0)))
    }, invertChild:function (a, b) {
      var c = b.style;
      W(a, {flip:"x", left:Z(c.width) - 10, top:Z(c.height) - 10, rotation:-90})
    }, symbols:{arc:function (a, b, c, d, e) {
      var f = e.start, g = e.end, c = e.r || c || d, d = Na(f), h = sa(f), j = Na(g), k = sa(g), e = e.innerR, i = 0.08 / c, m = e && 0.25 / e || 0;
      if (g - f === 0)return["x"]; else 2 * kb - g + f < i ? j = -i : g - f < m && (j = Na(f + m));
      return["wa", a - c, b - c, a + c, b + c, a + c * d, b + c * h, a + c * j, b + c * k, "at", a - e, b - e, a + e, b + e, a + e * j,
        b + e * k, a + e * d, b + e * h, "x", "e"]
    }, circle:function (a, b, c, d) {
      return["wa", a, b, a + c, b + d, a + c, b + d / 2, a + c, b + d / 2, "e"]
    }, rect:function (a, b, c, d, e) {
      if (!A(e))return[];
      var f = a + c, g = b + d, c = wa(e.r || 0, c, d);
      return[ya, a + c, b, ka, f - c, b, "wa", f - 2 * c, b, f, b + 2 * c, f - c, b, f, b + c, ka, f, g - c, "wa", f - 2 * c, g - 2 * c, f, g, f, g - c, f - c, g, ka, a + c, g, "wa", a, g - 2 * c, a + 2 * c, g, a + c, g, a, g - c, ka, a, b + c, "wa", a, b, a + 2 * c, b + 2 * c, a, b + c, a + c, b, "x", "e"]
    }}}, mb = function () {
    this.init.apply(this, arguments)
  }, mb.prototype = I(Eb.prototype, w), Sb = mb;
  var xc, Lc;
  rb && (xc = function () {
  }, Lc = function () {
    function a() {
      var a =
        b.length, d;
      for (d = 0; d < a; d++)b[d]();
      b = []
    }

    var b = [];
    return{push:function (c, d) {
      b.length === 0 && Rc(d, a);
      b.push(c)
    }}
  }());
  Sb = mb || xc || Eb;
  ec.prototype.callbacks = [];
  var ab = function () {
  };
  ab.prototype = {init:function (a, b, c) {
    var d = a.chart.counters;
    this.series = a;
    this.applyOptions(b, c);
    this.pointAttr = {};
    if (a.options.colorByPoint) {
      b = a.chart.options.colors;
      if (!this.options)this.options = {};
      this.color = this.options.color = this.color || b[d.color++];
      d.wrapColor(b.length)
    }
    a.chart.pointCount++;
    return this
  }, applyOptions:function (a, b) {
    var c = this.series, d = typeof a;
    this.config = a;
    if (d === "number" || a === null)this.y = a; else if (typeof a[0] === "number")this.x = a[0], this.y = a[1]; else if (d === "object" && typeof a.length !== "number") {
      if (G(this, a), this.options = a, a.dataLabels)c._hasPointLabels = !0
    } else if (typeof a[0] === "string")this.name = a[0], this.y = a[1];
    if (this.x === D)this.x = b === D ? c.autoIncrement() : b
  }, destroy:function () {
    var a = this.series, b = a.chart.hoverPoints, c;
    a.chart.pointCount--;
    b && (this.setState(), Lb(b, this));
    if (this === a.chart.hoverPoint)this.onMouseOut();
    a.chart.hoverPoints = null;
    if (this.graphic || this.dataLabel)ua(this), this.destroyElements();
    this.legendItem && this.series.chart.legend.destroyItem(this);
    for (c in this)this[c] = null
  }, destroyElements:function () {
    for (var a = "graphic,tracker,dataLabel,group,connector,shadowGroup".split(","), b, c = 6; c--;)b = a[c], this[b] && (this[b] = this[b].destroy())
  }, getLabelConfig:function () {
    return{x:this.category, y:this.y, key:this.name || this.category, series:this.series, point:this, percentage:this.percentage, total:this.total || this.stackTotal}
  },
    select:function (a, b) {
      var c = this, d = c.series.chart, a = r(a, !c.selected);
      c.firePointEvent(a ? "select" : "unselect", {accumulate:b}, function () {
        c.selected = a;
        c.setState(a && "select");
        b || q(d.getSelectedPoints(), function (a) {
          if (a.selected && a !== c)a.selected = !1, a.setState(ra), a.firePointEvent("unselect")
        })
      })
    }, onMouseOver:function () {
      var a = this.series, b = a.chart, c = b.tooltip, d = b.hoverPoint;
      if (d && d !== this)d.onMouseOut();
      this.firePointEvent("mouseOver");
      c && (!c.shared || a.noSharedTooltip) && c.refresh(this);
      this.setState(fb);
      b.hoverPoint = this
    }, onMouseOut:function () {
      this.firePointEvent("mouseOut");
      this.setState();
      this.series.chart.hoverPoint = null
    }, tooltipFormatter:function (a) {
      var b = this.series, c = b.tooltipOptions, d = String(this.y).split("."), d = d[1] ? d[1].length : 0, e = a.match(/\{(series|point)\.[a-zA-Z]+\}/g), f = /[{\.}]/, g, h, j, k;
      for (k in e)h = e[k], Gb(h) && h !== a && (j = (" " + h).split(f), g = {point:this, series:b}[j[1]], j = j[2], g = g === this && (j === "y" || j === "open" || j === "high" || j === "low" || j === "close") ? (c.valuePrefix || c.yPrefix || "") + Zb(this[j],
        r(c.valueDecimals, c.yDecimals, d)) + (c.valueSuffix || c.ySuffix || "") : g[j], a = a.replace(h, g));
      return a
    }, update:function (a, b, c) {
      var d = this, e = d.series, f = d.graphic, g, h = e.data, j = h.length, k = e.chart, b = r(b, !0);
      d.firePointEvent("update", {options:a}, function () {
        d.applyOptions(a);
        xb(a) && (e.getAttribs(), f && f.attr(d.pointAttr[e.state]));
        for (g = 0; g < j; g++)if (h[g] === d) {
          e.xData[g] = d.x;
          e.yData[g] = d.y;
          e.options.data[g] = a;
          break
        }
        e.isDirty = !0;
        e.isDirtyData = !0;
        b && k.redraw(c)
      })
    }, remove:function (a, b) {
      var c = this, d = c.series, e = d.chart,
        f, g = d.data, h = g.length;
      Ob(b, e);
      a = r(a, !0);
      c.firePointEvent("remove", null, function () {
        for (f = 0; f < h; f++)if (g[f] === c) {
          g.splice(f, 1);
          d.options.data.splice(f, 1);
          d.xData.splice(f, 1);
          d.yData.splice(f, 1);
          break
        }
        c.destroy();
        d.isDirty = !0;
        d.isDirtyData = !0;
        a && e.redraw()
      })
    }, firePointEvent:function (a, b, c) {
      var d = this, e = this.series.options;
      (e.point.events[a] || d.options && d.options.events && d.options.events[a]) && this.importEvents();
      a === "click" && e.allowPointSelect && (c = function (a) {
        d.select(null, a.ctrlKey || a.metaKey || a.shiftKey)
      });
      aa(this, a, b, c)
    }, importEvents:function () {
      if (!this.hasImportedEvents) {
        var a = I(this.series.options.point, this.options).events, b;
        this.events = a;
        for (b in a)X(this, b, a[b]);
        this.hasImportedEvents = !0
      }
    }, setState:function (a) {
      var b = this.plotX, c = this.plotY, d = this.series, e = d.options.states, f = J[d.type].marker && d.options.marker, g = f && !f.enabled, h = f && f.states[a], j = h && h.enabled === !1, k = d.stateMarkerGraphic, i = d.chart, m = this.pointAttr, a = a || ra;
      if (!(a === this.state || this.selected && a !== "select" || e[a] && e[a].enabled === !1 || a &&
        (j || g && !h.enabled))) {
        if (this.graphic)e = f && this.graphic.symbolName && m[a].r, this.graphic.attr(I(m[a], e ? {x:b - e, y:c - e, width:2 * e, height:2 * e} : {})); else {
          if (a) {
            if (!k)e = f.radius, d.stateMarkerGraphic = k = i.renderer.symbol(d.symbol, -e, -e, 2 * e, 2 * e).attr(m[a]).add(d.group);
            k.translate(b, c)
          }
          if (k)k[a ? "show" : "hide"]()
        }
        this.state = a
      }
    }};
  var ia = function () {
  };
  ia.prototype = {isCartesian:!0, type:"line", pointClass:ab, sorted:!0, pointAttrToOptions:{stroke:"lineColor", "stroke-width":"lineWidth", fill:"fillColor", r:"radius"}, init:function (a, b) {
    var c, d;
    d = a.series.length;
    this.chart = a;
    this.options = b = this.setOptions(b);
    this.bindAxes();
    G(this, {index:d, name:b.name || "Series " + (d + 1), state:ra, pointAttr:{}, visible:b.visible !== !1, selected:b.selected === !0});
    if (rb)b.animation = !1;
    d = b.events;
    for (c in d)X(this, c, d[c]);
    if (d && d.click || b.point && b.point.events && b.point.events.click || b.allowPointSelect)a.runTrackerClick = !0;
    this.getColor();
    this.getSymbol();
    this.setData(b.data, !1)
  }, bindAxes:function () {
    var a = this, b = a.options, c = a.chart, d;
    a.isCartesian && q(["xAxis",
      "yAxis"], function (e) {
      q(c[e], function (c) {
        d = c.options;
        if (b[e] === d.index || b[e] === D && d.index === 0)c.series.push(a), a[e] = c, c.isDirty = !0
      })
    })
  }, autoIncrement:function () {
    var a = this.options, b = this.xIncrement, b = r(b, a.pointStart, 0);
    this.pointInterval = r(this.pointInterval, a.pointInterval, 1);
    this.xIncrement = b + this.pointInterval;
    return b
  }, getSegments:function () {
    var a = -1, b = [], c, d = this.points, e = d.length;
    if (e)if (this.options.connectNulls) {
      for (c = e; c--;)d[c].y === null && d.splice(c, 1);
      d.length && (b = [d])
    } else q(d, function (c, g) {
      c.y === null ? (g > a + 1 && b.push(d.slice(a + 1, g)), a = g) : g === e - 1 && b.push(d.slice(a + 1, g + 1))
    });
    this.segments = b
  }, setOptions:function (a) {
    var b = this.chart.options, c = b.plotOptions, d = a.data;
    a.data = null;
    c = I(c[this.type], c.series, a);
    c.data = a.data = d;
    this.tooltipOptions = I(b.tooltip, c.tooltip);
    return c
  }, getColor:function () {
    var a = this.chart.options.colors, b = this.chart.counters;
    this.color = this.options.color || a[b.color++] || "#0000ff";
    b.wrapColor(a.length)
  }, getSymbol:function () {
    var a = this.options.marker, b = this.chart, c = b.options.symbols,
      b = b.counters;
    this.symbol = a.symbol || c[b.symbol++];
    if (/^url/.test(this.symbol))a.radius = 0;
    b.wrapSymbol(c.length)
  }, addPoint:function (a, b, c, d) {
    var e = this.data, f = this.graph, g = this.area, h = this.chart, j = this.xData, k = this.yData, i = f && f.shift || 0, m = this.options.data;
    Ob(d, h);
    if (f && c)f.shift = i + 1;
    if (g) {
      if (c)g.shift = i + 1;
      g.isArea = !0
    }
    b = r(b, !0);
    d = {series:this};
    this.pointClass.prototype.applyOptions.apply(d, [a]);
    j.push(d.x);
    k.push(this.valueCount === 4 ? [d.open, d.high, d.low, d.close] : d.y);
    m.push(a);
    c && (e[0] && e[0].remove ?
      e[0].remove(!1) : (e.shift(), j.shift(), k.shift(), m.shift()));
    this.getAttribs();
    this.isDirtyData = this.isDirty = !0;
    b && h.redraw()
  }, setData:function (a, b) {
    var c = this.points, d = this.options, e = this.initialColor, f = this.chart, g = null;
    this.xIncrement = null;
    this.pointRange = this.xAxis && this.xAxis.categories && 1 || d.pointRange;
    if (A(e))f.counters.color = e;
    var h = [], j = [], k = a ? a.length : [], i = this.valueCount === 4;
    if (k > (d.turboThreshold || 1E3)) {
      for (e = 0; g === null && e < k;)g = a[e], e++;
      if (Yb(g)) {
        g = r(d.pointStart, 0);
        d = r(d.pointInterval,
          1);
        for (e = 0; e < k; e++)h[e] = g, j[e] = a[e], g += d;
        this.xIncrement = g
      } else if (mc(g))if (i)for (e = 0; e < k; e++)d = a[e], h[e] = d[0], j[e] = d.slice(1, 5); else for (e = 0; e < k; e++)d = a[e], h[e] = d[0], j[e] = d[1]
    } else for (e = 0; e < k; e++)d = {series:this}, this.pointClass.prototype.applyOptions.apply(d, [a[e]]), h[e] = d.x, j[e] = i ? [d.open, d.high, d.low, d.close] : d.y;
    this.data = [];
    this.options.data = a;
    this.xData = h;
    this.yData = j;
    for (e = c && c.length || 0; e--;)c[e] && c[e].destroy && c[e].destroy();
    this.isDirty = this.isDirtyData = f.isDirtyBox = !0;
    r(b, !0) && f.redraw(!1)
  },
    remove:function (a, b) {
      var c = this, d = c.chart, a = r(a, !0);
      if (!c.isRemoving)c.isRemoving = !0, aa(c, "remove", null, function () {
        c.destroy();
        d.isDirtyLegend = d.isDirtyBox = !0;
        a && d.redraw(b)
      });
      c.isRemoving = !1
    }, processData:function (a) {
      var b = this.xData, c = this.yData, d = b.length, e = 0, f = d, g, h, j = this.xAxis, k = this.options, i = k.cropThreshold, m = this.isCartesian;
      if (m && !this.isDirty && !j.isDirty && !this.yAxis.isDirty && !a)return!1;
      if (m && this.sorted && (!i || d > i || this.forceCrop))if (a = j.getExtremes(), j = a.min, i = a.max, b[d - 1] < j || b[0] > i)b =
        [], c = []; else if (b[0] < j || b[d - 1] > i) {
        for (a = 0; a < d; a++)if (b[a] >= j) {
          e = O(0, a - 1);
          break
        }
        for (; a < d; a++)if (b[a] > i) {
          f = a + 1;
          break
        }
        b = b.slice(e, f);
        c = c.slice(e, f);
        g = !0
      }
      for (a = b.length - 1; a > 0; a--)if (d = b[a] - b[a - 1], d > 0 && (h === D || d < h))h = d;
      this.cropped = g;
      this.cropStart = e;
      this.processedXData = b;
      this.processedYData = c;
      if (k.pointRange === null)this.pointRange = h || 1;
      this.closestPointRange = h
    }, generatePoints:function () {
      var a = this.options.data, b = this.data, c, d = this.processedXData, e = this.processedYData, f = this.pointClass, g = d.length, h = this.cropStart ||
        0, j, k = this.hasGroupedData, i, m = [], l;
      if (!b && !k)b = [], b.length = a.length, b = this.data = b;
      for (l = 0; l < g; l++)j = h + l, k ? m[l] = (new f).init(this, [d[l]].concat(zb(e[l]))) : (b[j] ? i = b[j] : b[j] = i = (new f).init(this, a[j], d[l]), m[l] = i);
      if (b && (g !== (c = b.length) || k))for (l = 0; l < c; l++)l === h && !k && (l += g), b[l] && b[l].destroyElements();
      this.data = b;
      this.points = m
    }, translate:function () {
      this.processedXData || this.processData();
      this.generatePoints();
      for (var a = this.chart, b = this.options, c = b.stacking, d = this.xAxis, e = d.categories, f = this.yAxis,
             g = this.points, h = g.length, j = !!this.modifyValue, k, i = f.series, m = i.length; m--;)if (i[m].visible) {
        m === this.index && (k = !0);
        break
      }
      for (m = 0; m < h; m++) {
        var i = g[m], l = i.x, o = i.y, t = i.low, q = f.stacks[(o < b.threshold ? "-" : "") + this.stackKey];
        i.plotX = x(d.translate(l, 0, 0, 0, 1) * 10) / 10;
        if (c && this.visible && q && q[l]) {
          t = q[l];
          l = t.total;
          t.cum = t = t.cum - o;
          o = t + o;
          if (k)t = b.threshold;
          c === "percent" && (t = l ? t * 100 / l : 0, o = l ? o * 100 / l : 0);
          i.percentage = l ? i.y * 100 / l : 0;
          i.stackTotal = l;
          i.stackY = o
        }
        i.yBottom = A(t) ? f.translate(t, 0, 1, 0, 1) : null;
        j && (o = this.modifyValue(o,
          i));
        i.plotY = typeof o === "number" ? x(f.translate(o, 0, 1, 0, 1) * 10) / 10 : D;
        i.clientX = a.inverted ? a.plotHeight - i.plotX : i.plotX;
        i.category = e && e[i.x] !== D ? e[i.x] : i.x
      }
      this.getSegments()
    }, setTooltipPoints:function (a) {
      var b = this.chart, c = b.inverted, d = [], b = x((c ? b.plotTop : b.plotLeft) + b.plotSizeX), e, f;
      e = this.xAxis;
      var g, h, j = [];
      if (this.options.enableMouseTracking !== !1) {
        if (a)this.tooltipPoints = null;
        q(this.segments || this.points, function (a) {
          d = d.concat(a)
        });
        e && e.reversed && (d = d.reverse());
        a = d.length;
        for (h = 0; h < a; h++) {
          g = d[h];
          e = d[h - 1] ? d[h - 1]._high + 1 : 0;
          for (f = g._high = d[h + 1] ? La((g.plotX + (d[h + 1] ? d[h + 1].plotX : b)) / 2) : b; e <= f;)j[c ? b - e++ : e++] = g
        }
        this.tooltipPoints = j
      }
    }, tooltipHeaderFormatter:function (a) {
      var b = this.tooltipOptions, c = b.xDateFormat || "%A, %b %e, %Y", d = this.xAxis;
      return b.headerFormat.replace("{point.key}", d && d.options.type === "datetime" ? Bb(c, a) : a).replace("{series.name}", this.name).replace("{series.color}", this.color)
    }, onMouseOver:function () {
      var a = this.chart, b = a.hoverSeries;
      if (Fa || !a.mouseIsDown) {
        if (b && b !== this)b.onMouseOut();
        this.options.events.mouseOver && aa(this, "mouseOver");
        this.setState(fb);
        a.hoverSeries = this
      }
    }, onMouseOut:function () {
      var a = this.options, b = this.chart, c = b.tooltip, d = b.hoverPoint;
      if (d)d.onMouseOut();
      this && a.events.mouseOut && aa(this, "mouseOut");
      c && !a.stickyTracking && !c.shared && c.hide();
      this.setState();
      b.hoverSeries = null
    }, animate:function (a) {
      var b = this.chart, c = this.clipRect, d = this.options.animation;
      d && !xb(d) && (d = {});
      if (a) {
        if (!c.isAnimating)c.attr("width", 0), c.isAnimating = !0
      } else c.animate({width:b.plotSizeX},
        d), this.animate = null
    }, drawPoints:function () {
      var a, b = this.points, c = this.chart, d, e, f, g, h, j, k, i;
      if (this.options.marker.enabled)for (f = b.length; f--;)if (g = b[f], d = g.plotX, e = g.plotY, i = g.graphic, e !== D && !isNaN(e))if (a = g.pointAttr[g.selected ? "select" : ra], h = a.r, j = r(g.marker && g.marker.symbol, this.symbol), k = j.indexOf("url") === 0, i)i.animate(G({x:d - h, y:e - h}, i.symbolName ? {width:2 * h, height:2 * h} : {})); else if (h > 0 || k)g.graphic = c.renderer.symbol(j, d - h, e - h, 2 * h, 2 * h).attr(a).add(this.group)
    }, convertAttribs:function (a, b, c, d) {
      var e = this.pointAttrToOptions, f, g, h = {}, a = a || {}, b = b || {}, c = c || {}, d = d || {};
      for (f in e)g = e[f], h[f] = r(a[g], b[f], c[f], d[f]);
      return h
    }, getAttribs:function () {
      var a = this, b = J[a.type].marker ? a.options.marker : a.options, c = b.states, d = c[fb], e, f = a.color, g = {stroke:f, fill:f}, h = a.points, j = [], k, i = a.pointAttrToOptions, m;
      a.options.marker ? (d.radius = d.radius || b.radius + 2, d.lineWidth = d.lineWidth || b.lineWidth + 1) : d.color = d.color || oa(d.color || f).brighten(d.brightness).get();
      j[ra] = a.convertAttribs(b, g);
      q([fb, "select"], function (b) {
        j[b] =
          a.convertAttribs(c[b], j[ra])
      });
      a.pointAttr = j;
      for (f = h.length; f--;) {
        g = h[f];
        if ((b = g.options && g.options.marker || g.options) && b.enabled === !1)b.radius = 0;
        e = !1;
        if (g.options)for (m in i)A(b[i[m]]) && (e = !0);
        if (e) {
          k = [];
          c = b.states || {};
          e = c[fb] = c[fb] || {};
          if (!a.options.marker)e.color = oa(e.color || g.options.color).brighten(e.brightness || d.brightness).get();
          k[ra] = a.convertAttribs(b, j[ra]);
          k[fb] = a.convertAttribs(c[fb], j[fb], k[ra]);
          k.select = a.convertAttribs(c.select, j.select, k[ra])
        } else k = j;
        g.pointAttr = k
      }
    }, destroy:function () {
      var a =
        this, b = a.chart, c = a.clipRect, d = /AppleWebKit\/533/.test(lb), e, f, g = a.data || [], h, j, k;
      aa(a, "destroy");
      ua(a);
      q(["xAxis", "yAxis"], function (b) {
        if (k = a[b])Lb(k.series, a), k.isDirty = !0
      });
      a.legendItem && a.chart.legend.destroyItem(a);
      for (f = g.length; f--;)(h = g[f]) && h.destroy && h.destroy();
      a.points = null;
      if (c && c !== b.clipRect)a.clipRect = c.destroy();
      q(["area", "graph", "dataLabelsGroup", "group", "tracker"], function (b) {
        a[b] && (e = d && b === "group" ? "hide" : "destroy", a[b][e]())
      });
      if (b.hoverSeries === a)b.hoverSeries = null;
      Lb(b.series,
        a);
      for (j in a)delete a[j]
    }, drawDataLabels:function () {
      var a = this, b = a.options, c = b.dataLabels;
      if (c.enabled || a._hasPointLabels) {
        var d, e, f = a.points, g, h, j, k = a.dataLabelsGroup, i = a.chart, m = a.xAxis, m = m ? m.left : i.plotLeft, l = a.yAxis, l = l ? l.top : i.plotTop, o = i.renderer, t = i.inverted, u = a.type, v = b.stacking, s = u === "column" || u === "bar", Y = c.verticalAlign === null, p = c.y === null, qa = o.fontMetrics(c.style.fontSize), M = qa.h, w = qa.b, N, F;
        s && (qa = {top:w, middle:w - M / 2, bottom:-M + w}, v ? (Y && (c = I(c, {verticalAlign:"middle"})), p && (c = I(c, {y:qa[c.verticalAlign]}))) :
          Y ? c = I(c, {verticalAlign:"top"}) : p && (c = I(c, {y:qa[c.verticalAlign]})));
        k ? k.translate(m, l) : k = a.dataLabelsGroup = o.g("data-labels").attr({visibility:a.visible ? $a : Xa, zIndex:6}).translate(m, l).add();
        h = c;
        q(f, function (f) {
          N = f.dataLabel;
          c = h;
          (g = f.options) && g.dataLabels && (c = I(c, g.dataLabels));
          if (F = c.enabled) {
            var m = f.barX && f.barX + f.barW / 2 || r(f.plotX, -999), l = r(f.plotY, -999), p = c.y === null ? f.y >= b.threshold ? -M + w : w : c.y;
            d = (t ? i.plotWidth - l : m) + c.x;
            e = x((t ? i.plotHeight - m : l) + p)
          }
          if (N && a.isCartesian && (!i.isInsidePlot(d, e) || !F))f.dataLabel =
            N.destroy(); else if (F) {
            m = c.align;
            j = c.formatter.call(f.getLabelConfig(), c);
            u === "column" && (d += {left:-1, right:1}[m] * f.barW / 2 || 0);
            !v && t && f.y < 0 && (m = "right", d -= 10);
            c.style.color = r(c.color, c.style.color, a.color, "black");
            if (N)N.attr({text:j}).animate({x:d, y:e}); else if (A(j))N = f.dataLabel = o[c.rotation ? "text" : "label"](j, d, e, null, null, null, c.useHTML, !0).attr({align:m, fill:c.backgroundColor, stroke:c.borderColor, "stroke-width":c.borderWidth, r:c.borderRadius, rotation:c.rotation, padding:c.padding, zIndex:1}).css(c.style).add(k).shadow(c.shadow);
            if (s && b.stacking && N)m = f.barX, l = f.barY, p = f.barW, f = f.barH, N.align(c, null, {x:t ? i.plotWidth - l - f : m, y:t ? i.plotHeight - m - p : l, width:t ? f : p, height:t ? p : f})
          }
        })
      }
    }, drawGraph:function () {
      var a = this, b = a.options, c = a.graph, d = [], e, f = a.area, g = a.group, h = b.lineColor || a.color, j = b.lineWidth, k = b.dashStyle, i, m = a.chart.renderer, l = a.yAxis.getThreshold(b.threshold), o = /^area/.test(a.type), t = [], u = [];
      q(a.segments, function (c) {
        i = [];
        q(c, function (d, e) {
          a.getPointSpline ? i.push.apply(i, a.getPointSpline(c, d, e)) : (i.push(e ? ka : ya), e && b.step &&
            i.push(d.plotX, c[e - 1].plotY), i.push(d.plotX, d.plotY))
        });
        c.length > 1 ? d = d.concat(i) : t.push(c[0]);
        if (o) {
          var e = [], f, g = i.length;
          for (f = 0; f < g; f++)e.push(i[f]);
          g === 3 && e.push(ka, i[1], i[2]);
          if (b.stacking && a.type !== "areaspline")for (f = c.length - 1; f >= 0; f--)f < c.length - 1 && b.step && e.push(c[f + 1].plotX, c[f].yBottom), e.push(c[f].plotX, c[f].yBottom); else e.push(ka, c[c.length - 1].plotX, l, ka, c[0].plotX, l);
          u = u.concat(e)
        }
      });
      a.graphPath = d;
      a.singlePoints = t;
      if (o)e = r(b.fillColor, oa(a.color).setOpacity(b.fillOpacity || 0.75).get()),
        f ? f.animate({d:u}) : a.area = a.chart.renderer.path(u).attr({fill:e}).add(g);
      if (c)Rb(c), c.animate({d:d}); else if (j) {
        c = {stroke:h, "stroke-width":j};
        if (k)c.dashstyle = k;
        a.graph = m.path(d).attr(c).add(g).shadow(b.shadow)
      }
    }, invertGroups:function () {
      function a() {
        var a = {width:b.yAxis.len, height:b.xAxis.len};
        c.attr(a).invert();
        d && d.attr(a).invert()
      }

      var b = this, c = b.group, d = b.trackerGroup, e = b.chart;
      X(e, "resize", a);
      X(b, "destroy", function () {
        ua(e, "resize", a)
      });
      a();
      b.invertGroups = a
    }, render:function () {
      var a = this, b = a.chart,
        c, d = a.options, e = d.clip !== !1, f = d.animation, g = f && a.animate, f = g ? f && f.duration || 500 : 0, h = a.clipRect, j = b.renderer;
      if (!h && (h = a.clipRect = !b.hasRendered && b.clipRect ? b.clipRect : j.clipRect(0, 0, b.plotSizeX, b.plotSizeY + 1), !b.clipRect))b.clipRect = h;
      if (!a.group)c = a.group = j.g("series"), c.attr({visibility:a.visible ? $a : Xa, zIndex:d.zIndex}).translate(a.xAxis.left, a.yAxis.top).add(b.seriesGroup);
      a.drawDataLabels();
      g && a.animate(!0);
      a.getAttribs();
      a.drawGraph && a.drawGraph();
      a.drawPoints();
      a.options.enableMouseTracking !==
        !1 && a.drawTracker();
      b.inverted && a.invertGroups();
      e && !a.hasRendered && (c.clip(h), a.trackerGroup && a.trackerGroup.clip(b.clipRect));
      g && a.animate();
      setTimeout(function () {
        h.isAnimating = !1;
        if ((c = a.group) && h !== b.clipRect && h.renderer) {
          if (e)c.clip(a.clipRect = b.clipRect);
          h.destroy()
        }
      }, f);
      a.isDirty = a.isDirtyData = !1;
      a.hasRendered = !0
    }, redraw:function () {
      var a = this.chart, b = this.isDirtyData, c = this.group;
      c && (a.inverted && c.attr({width:a.plotWidth, height:a.plotHeight}), c.animate({translateX:this.xAxis.left, translateY:this.yAxis.top}));
      this.translate();
      this.setTooltipPoints(!0);
      this.render();
      b && aa(this, "updatedData")
    }, setState:function (a) {
      var b = this.options, c = this.graph, d = b.states, b = b.lineWidth, a = a || ra;
      if (this.state !== a)this.state = a, d[a] && d[a].enabled === !1 || (a && (b = d[a].lineWidth || b + 1), c && !c.dashstyle && c.attr({"stroke-width":b}, a ? 0 : 500))
    }, setVisible:function (a, b) {
      var c = this.chart, d = this.legendItem, e = this.group, f = this.tracker, g = this.dataLabelsGroup, h, j = this.points, k = c.options.chart.ignoreHiddenSeries;
      h = this.visible;
      h = (this.visible =
        a = a === D ? !h : a) ? "show" : "hide";
      if (e)e[h]();
      if (f)f[h](); else if (j)for (e = j.length; e--;)if (f = j[e], f.tracker)f.tracker[h]();
      if (g)g[h]();
      d && c.legend.colorizeItem(this, a);
      this.isDirty = !0;
      this.options.stacking && q(c.series, function (a) {
        if (a.options.stacking && a.visible)a.isDirty = !0
      });
      if (k)c.isDirtyBox = !0;
      b !== !1 && c.redraw();
      aa(this, h)
    }, show:function () {
      this.setVisible(!0)
    }, hide:function () {
      this.setVisible(!1)
    }, select:function (a) {
      this.selected = a = a === D ? !this.selected : a;
      if (this.checkbox)this.checkbox.checked = a;
      aa(this,
        a ? "select" : "unselect")
    }, drawTrackerGroup:function () {
      var a = this.trackerGroup, b = this.chart;
      if (this.isCartesian) {
        if (!a)this.trackerGroup = a = b.renderer.g().attr({zIndex:this.options.zIndex || 1}).add(b.trackerGroup);
        a.translate(this.xAxis.left, this.yAxis.top)
      }
      return a
    }, drawTracker:function () {
      var a = this, b = a.options, c = [].concat(a.graphPath), d = c.length, e = a.chart, f = e.renderer, g = e.options.tooltip.snap, h = a.tracker, j = b.cursor, j = j && {cursor:j}, k = a.singlePoints, i = a.drawTrackerGroup(), m;
      if (d)for (m = d + 1; m--;)c[m] ===
        ya && c.splice(m + 1, 0, c[m + 1] - g, c[m + 2], ka), (m && c[m] === ya || m === d) && c.splice(m, 0, ka, c[m - 2] + g, c[m - 1]);
      for (m = 0; m < k.length; m++)d = k[m], c.push(ya, d.plotX - g, d.plotY, ka, d.plotX + g, d.plotY);
      h ? h.attr({d:c}) : a.tracker = f.path(c).attr({isTracker:!0, stroke:Qc, fill:Ka, "stroke-linejoin":"bevel", "stroke-width":b.lineWidth + 2 * g, visibility:a.visible ? $a : Xa}).on(Fa ? "touchstart" : "mouseover",function () {
        if (e.hoverSeries !== a)a.onMouseOver()
      }).on("mouseout",function () {
          if (!b.stickyTracking)a.onMouseOut()
        }).css(j).add(i)
    }};
  w = ea(ia);
  ma.line = w;
  w = ea(ia, {type:"area"});
  ma.area = w;
  w = ea(ia, {type:"spline", getPointSpline:function (a, b, c) {
    var d = b.plotX, e = b.plotY, f = a[c - 1], g = a[c + 1], h, j, k, i;
    if (c && c < a.length - 1) {
      a = f.plotY;
      k = g.plotX;
      var g = g.plotY, m;
      h = (1.5 * d + f.plotX) / 2.5;
      j = (1.5 * e + a) / 2.5;
      k = (1.5 * d + k) / 2.5;
      i = (1.5 * e + g) / 2.5;
      m = (i - j) * (k - d) / (k - h) + e - i;
      j += m;
      i += m;
      j > a && j > e ? (j = O(a, e), i = 2 * e - j) : j < a && j < e && (j = wa(a, e), i = 2 * e - j);
      i > g && i > e ? (i = O(g, e), j = 2 * e - i) : i < g && i < e && (i = wa(g, e), j = 2 * e - i);
      b.rightContX = k;
      b.rightContY = i
    }
    c ? (b = ["C", f.rightContX || f.plotX, f.rightContY || f.plotY,
      h || d, j || e, d, e], f.rightContX = f.rightContY = null) : b = [ya, d, e];
    return b
  }});
  ma.spline = w;
  w = ea(w, {type:"areaspline"});
  ma.areaspline = w;
  var jc = ea(ia, {type:"column", tooltipOutsidePlot:!0, pointAttrToOptions:{stroke:"borderColor", "stroke-width":"borderWidth", fill:"color", r:"borderRadius"}, init:function () {
    ia.prototype.init.apply(this, arguments);
    var a = this, b = a.chart;
    b.hasRendered && q(b.series, function (b) {
      if (b.type === a.type)b.isDirty = !0
    })
  }, translate:function () {
    var a = this, b = a.chart, c = a.options, d = c.stacking, e = c.borderWidth,
      f = 0, g = a.xAxis, h = g.reversed, j = {}, k, i;
    ia.prototype.translate.apply(a);
    q(b.series, function (b) {
      if (b.type === a.type && b.visible && a.options.group === b.options.group)b.options.stacking ? (k = b.stackKey, j[k] === D && (j[k] = f++), i = j[k]) : i = f++, b.columnIndex = i
    });
    var b = a.points, g = Ga(g.translationSlope) * (g.ordinalSlope || g.closestPointRange || 1), m = g * c.groupPadding, l = (g - 2 * m) / f, o = c.pointWidth, t = A(o) ? (l - o) / 2 : l * c.pointPadding, u = gc(O(r(o, l - 2 * t), 1 + 2 * e)), v = t + (m + ((h ? f - a.columnIndex : a.columnIndex) || 0) * l - g / 2) * (h ? -1 : 1), s = a.yAxis.getThreshold(c.threshold),
      w = r(c.minPointLength, 5);
    q(b, function (b) {
      var f = b.plotY, g = r(b.yBottom, s), h = b.plotX + v, j = gc(wa(f, g)), i = gc(O(f, g) - j), k = a.yAxis.stacks[(b.y < 0 ? "-" : "") + a.stackKey];
      d && a.visible && k && k[b.x] && k[b.x].setOffset(v, u);
      Ga(i) < w && w && (i = w, j = Ga(j - s) > w ? g - w : s - (f <= s ? w : 0));
      G(b, {barX:h, barY:j, barW:u, barH:i});
      b.shapeType = "rect";
      f = {x:h, y:j, width:u, height:i, r:c.borderRadius, strokeWidth:e};
      e % 2 && (f.y -= 1, f.height += 1);
      b.shapeArgs = f;
      b.trackerArgs = Ga(i) < 3 && I(b.shapeArgs, {height:6, y:j - 3})
    })
  }, getSymbol:function () {
  }, drawGraph:function () {
  },
    drawPoints:function () {
      var a = this, b = a.options, c = a.chart.renderer, d, e;
      q(a.points, function (f) {
        var g = f.plotY;
        if (g !== D && !isNaN(g) && f.y !== null)d = f.graphic, e = f.shapeArgs, d ? (Rb(d), d.animate(c.Element.prototype.crisp.apply({}, [e.strokeWidth, e.x, e.y, e.width, e.height]))) : f.graphic = d = c[f.shapeType](e).attr(f.pointAttr[f.selected ? "select" : ra]).add(a.group).shadow(b.shadow)
      })
    }, drawTracker:function () {
      var a = this, b = a.chart, c = b.renderer, d, e, f = +new Date, g = a.options, h = g.cursor, j = h && {cursor:h}, k = a.drawTrackerGroup(),
        i;
      q(a.points, function (h) {
        e = h.tracker;
        d = h.trackerArgs || h.shapeArgs;
        delete d.strokeWidth;
        if (h.y !== null)e ? e.attr(d) : h.tracker = c[h.shapeType](d).attr({isTracker:f, fill:Qc, visibility:a.visible ? $a : Xa}).on(Fa ? "touchstart" : "mouseover",function (c) {
          i = c.relatedTarget || c.fromElement;
          if (b.hoverSeries !== a && $(i, "isTracker") !== f)a.onMouseOver();
          h.onMouseOver()
        }).on("mouseout",function (b) {
            if (!g.stickyTracking && (i = b.relatedTarget || b.toElement, $(i, "isTracker") !== f))a.onMouseOut()
          }).css(j).add(h.group || k)
      })
    }, animate:function (a) {
      var b =
        this, c = b.points, d = b.options;
      if (!a)q(c, function (a) {
        var c = a.graphic, a = a.shapeArgs, g = b.yAxis, h = d.threshold;
        c && (c.attr({height:0, y:A(h) ? g.getThreshold(h) : g.translate(g.getExtremes().min, 0, 1, 0, 1)}), c.animate({height:a.height, y:a.y}, d.animation))
      }), b.animate = null
    }, remove:function () {
      var a = this, b = a.chart;
      b.hasRendered && q(b.series, function (b) {
        if (b.type === a.type)b.isDirty = !0
      });
      ia.prototype.remove.apply(a, arguments)
    }});
  ma.column = jc;
  w = ea(jc, {type:"bar", init:function () {
    this.inverted = !0;
    jc.prototype.init.apply(this,
      arguments)
  }});
  ma.bar = w;
  w = ea(ia, {type:"scatter", sorted:!1, translate:function () {
    var a = this;
    ia.prototype.translate.apply(a);
    q(a.points, function (b) {
      b.shapeType = "circle";
      b.shapeArgs = {x:b.plotX, y:b.plotY, r:a.chart.options.tooltip.snap}
    })
  }, drawTracker:function () {
    for (var a = this, b = a.options.cursor, b = b && {cursor:b}, c = a.points, d = c.length, e; d--;)if (e = c[d].graphic)e.element._i = d;
    a._hasTracking ? a._hasTracking = !0 : a.group.attr({isTracker:!0}).on(Fa ? "touchstart" : "mouseover",function (b) {
      a.onMouseOver();
      if (b.target._i !==
        D)c[b.target._i].onMouseOver()
    }).on("mouseout",function () {
        if (!a.options.stickyTracking)a.onMouseOut()
      }).css(b)
  }});
  ma.scatter = w;
  w = ea(ab, {init:function () {
    ab.prototype.init.apply(this, arguments);
    var a = this, b;
    G(a, {visible:a.visible !== !1, name:r(a.name, "Slice")});
    b = function () {
      a.slice()
    };
    X(a, "select", b);
    X(a, "unselect", b);
    return a
  }, setVisible:function (a) {
    var b = this.series.chart, c = this.tracker, d = this.dataLabel, e = this.connector, f = this.shadowGroup, g;
    g = (this.visible = a = a === D ? !this.visible : a) ? "show" : "hide";
    this.group[g]();
    if (c)c[g]();
    if (d)d[g]();
    if (e)e[g]();
    if (f)f[g]();
    this.legendItem && b.legend.colorizeItem(this, a)
  }, slice:function (a, b, c) {
    var d = this.series.chart, e = this.slicedTranslation;
    Ob(c, d);
    r(b, !0);
    a = this.sliced = A(a) ? a : !this.sliced;
    a = {translateX:a ? e[0] : d.plotLeft, translateY:a ? e[1] : d.plotTop};
    this.group.animate(a);
    this.shadowGroup && this.shadowGroup.animate(a)
  }});
  w = ea(ia, {type:"pie", isCartesian:!1, pointClass:w, pointAttrToOptions:{stroke:"borderColor", "stroke-width":"borderWidth", fill:"color"}, getColor:function () {
    this.initialColor =
      this.chart.counters.color
  }, animate:function () {
    var a = this;
    q(a.points, function (b) {
      var c = b.graphic, b = b.shapeArgs, d = -kb / 2;
      c && (c.attr({r:0, start:d, end:d}), c.animate({r:b.r, start:b.start, end:b.end}, a.options.animation))
    });
    a.animate = null
  }, setData:function () {
    ia.prototype.setData.apply(this, arguments);
    this.processData();
    this.generatePoints()
  }, translate:function () {
    this.generatePoints();
    var a = 0, b = -0.25, c = this.options, d = c.slicedOffset, e = d + c.borderWidth, f = c.center.concat([c.size, c.innerSize || 0]), g = this.chart,
      h = g.plotWidth, j = g.plotHeight, k, i, m, l = this.points, o = 2 * kb, t, u = wa(h, j), v, s, r, p = c.dataLabels.distance, f = Kb(f, function (a, b) {
        return(v = /%$/.test(a)) ? [h, j, u, u][b] * Z(a) / 100 : a
      });
    this.getX = function (a, b) {
      m = va.asin((a - f[1]) / (f[2] / 2 + p));
      return f[0] + (b ? -1 : 1) * Na(m) * (f[2] / 2 + p)
    };
    this.center = f;
    q(l, function (b) {
      a += b.y
    });
    q(l, function (c) {
      t = a ? c.y / a : 0;
      k = x(b * o * 1E3) / 1E3;
      b += t;
      i = x(b * o * 1E3) / 1E3;
      c.shapeType = "arc";
      c.shapeArgs = {x:f[0], y:f[1], r:f[2] / 2, innerR:f[3] / 2, start:k, end:i};
      m = (i + k) / 2;
      c.slicedTranslation = Kb([Na(m) * d + g.plotLeft,
        sa(m) * d + g.plotTop], x);
      s = Na(m) * f[2] / 2;
      r = sa(m) * f[2] / 2;
      c.tooltipPos = [f[0] + s * 0.7, f[1] + r * 0.7];
      c.labelPos = [f[0] + s + Na(m) * p, f[1] + r + sa(m) * p, f[0] + s + Na(m) * e, f[1] + r + sa(m) * e, f[0] + s, f[1] + r, p < 0 ? "center" : m < o / 4 ? "left" : "right", m];
      c.percentage = t * 100;
      c.total = a
    });
    this.setTooltipPoints()
  }, render:function () {
    this.getAttribs();
    this.drawPoints();
    this.options.enableMouseTracking !== !1 && this.drawTracker();
    this.drawDataLabels();
    this.options.animation && this.animate && this.animate();
    this.isDirty = !1
  }, drawPoints:function () {
    var a = this.chart,
      b = a.renderer, c, d, e, f = this.options.shadow, g, h;
    q(this.points, function (j) {
      d = j.graphic;
      h = j.shapeArgs;
      e = j.group;
      g = j.shadowGroup;
      if (f && !g)g = j.shadowGroup = b.g("shadow").attr({zIndex:4}).add();
      if (!e)e = j.group = b.g("point").attr({zIndex:5}).add();
      c = j.sliced ? j.slicedTranslation : [a.plotLeft, a.plotTop];
      e.translate(c[0], c[1]);
      g && g.translate(c[0], c[1]);
      d ? d.animate(h) : j.graphic = b.arc(h).attr(G(j.pointAttr[ra], {"stroke-linejoin":"round"})).add(j.group).shadow(f, g);
      j.visible === !1 && j.setVisible(!1)
    })
  }, drawDataLabels:function () {
    var a =
      this.data, b, c = this.chart, d = this.options.dataLabels, e = r(d.connectorPadding, 10), f = r(d.connectorWidth, 1), g, h, j = r(d.softConnector, !0), k = d.distance, i = this.center, m = i[2] / 2, i = i[1], l = k > 0, o = [
      [],
      []
    ], t, u, v, s, w = 2, p;
    if (d.enabled) {
      ia.prototype.drawDataLabels.apply(this);
      q(a, function (a) {
        a.dataLabel && o[a.labelPos[7] < kb / 2 ? 0 : 1].push(a)
      });
      o[1].reverse();
      s = function (a, b) {
        return b.y - a.y
      };
      for (a = o[0][0] && o[0][0].dataLabel && o[0][0].dataLabel.getBBox().height; w--;) {
        var x = [], M = [], A = o[w], N = A.length, F;
        for (p = i - m - k; p <= i + m + k; p +=
          a)x.push(p);
        v = x.length;
        if (N > v) {
          h = [].concat(A);
          h.sort(s);
          for (p = N; p--;)h[p].rank = p;
          for (p = N; p--;)A[p].rank >= v && A.splice(p, 1);
          N = A.length
        }
        for (p = 0; p < N; p++) {
          b = A[p];
          h = b.labelPos;
          b = 9999;
          for (u = 0; u < v; u++)g = Ga(x[u] - h[1]), g < b && (b = g, F = u);
          if (F < p && x[p] !== null)F = p; else for (v < N - p + F && x[p] !== null && (F = v - N + p); x[F] === null;)F++;
          M.push({i:F, y:x[F]});
          x[F] = null
        }
        M.sort(s);
        for (p = 0; p < N; p++) {
          b = A[p];
          h = b.labelPos;
          g = b.dataLabel;
          u = M.pop();
          t = h[1];
          v = b.visible === !1 ? Xa : $a;
          F = u.i;
          u = u.y;
          if (t > u && x[F + 1] !== null || t < u && x[F - 1] !== null)u = t;
          t = this.getX(F ===
            0 || F === x.length - 1 ? t : u, w);
          g.attr({visibility:v, align:h[6]})[g.moved ? "animate" : "attr"]({x:t + d.x + ({left:e, right:-e}[h[6]] || 0), y:u + d.y});
          g.moved = !0;
          if (l && f)g = b.connector, h = j ? [ya, t + (h[6] === "left" ? 5 : -5), u, "C", t, u, 2 * h[2] - h[4], 2 * h[3] - h[5], h[2], h[3], ka, h[4], h[5]] : [ya, t + (h[6] === "left" ? 5 : -5), u, ka, h[2], h[3], ka, h[4], h[5]], g ? (g.animate({d:h}), g.attr("visibility", v)) : b.connector = g = this.chart.renderer.path(h).attr({"stroke-width":f, stroke:d.connectorColor || b.color || "#606060", visibility:v, zIndex:3}).translate(c.plotLeft,
            c.plotTop).add()
        }
      }
    }
  }, drawTracker:jc.prototype.drawTracker, getSymbol:function () {
  }});
  ma.pie = w;
  var C = ia.prototype, cd = C.processData, dd = C.generatePoints, ed = C.destroy, fd = C.tooltipHeaderFormatter, w = {approximation:"average", groupPixelWidth:2, dateTimeLabelFormats:Ja(Hb, ["%A, %b %e, %H:%M:%S.%L", "%A, %b %e, %H:%M:%S.%L", "-%H:%M:%S.%L"], ob, ["%A, %b %e, %H:%M:%S", "%A, %b %e, %H:%M:%S", "-%H:%M:%S"], cb, ["%A, %b %e, %H:%M", "%A, %b %e, %H:%M", "-%H:%M"], db, ["%A, %b %e, %H:%M", "%A, %b %e, %H:%M", "-%H:%M"], P, ["%A, %b %e, %Y",
    "%A, %b %e", "-%A, %b %e, %Y"], Ca, ["Week from %A, %b %e, %Y", "%A, %b %e", "-%A, %b %e, %Y"], pa, ["%B %Y", "%B", "-%B %Y"], fa, ["%Y", "%Y", "-%Y"])}, Uc = [
    [Hb, [1, 2, 5, 10, 20, 25, 50, 100, 200, 500]],
    [ob, [1, 2, 5, 10, 15, 30]],
    [cb, [1, 2, 5, 10, 15, 30]],
    [db, [1, 2, 3, 4, 6, 8, 12]],
    [P, [1]],
    [Ca, [1]],
    [pa, [1, 3, 6]],
    [fa, null]
  ], wb = {sum:function (a) {
    var b = a.length, c;
    if (!b && a.hasNulls)c = null; else if (b)for (c = 0; b--;)c += a[b];
    return c
  }, average:function (a) {
    var b = a.length, a = wb.sum(a);
    typeof a === "number" && b && (a /= b);
    return a
  }, open:function (a) {
    return a.length ?
      a[0] : a.hasNulls ? null : D
  }, high:function (a) {
    return a.length ? Ib(a) : a.hasNulls ? null : D
  }, low:function (a) {
    return a.length ? Mb(a) : a.hasNulls ? null : D
  }, close:function (a) {
    return a.length ? a[a.length - 1] : a.hasNulls ? null : D
  }, ohlc:function (a, b, c, d) {
    a = wb.open(a);
    b = wb.high(b);
    c = wb.low(c);
    d = wb.close(d);
    if (typeof a === "number" || typeof b === "number" || typeof c === "number" || typeof d === "number")return[a, b, c, d]
  }};
  C.groupData = function (a, b, c, d) {
    var e = this.data, f = this.options.data, g = [], h = [], j = a.length, k, i, m = !!b;
    i = [];
    var l = [], o = [],
      q = [], u = typeof d === "function" ? d : wb[d], r;
    for (r = 0; r <= j; r++) {
      for (; c[1] !== D && a[r] >= c[1] || r === j;)if (k = c.shift(), i = u(i, l, o, q), i !== D && (g.push(k), h.push(i)), i = [], l = [], o = [], q = [], r === j)break;
      if (r === j)break;
      k = m ? b[r] : null;
      if (d === "ohlc") {
        k = this.cropStart + r;
        var s = e && e[k] || this.pointClass.prototype.applyOptions.apply({}, [f[k]]);
        k = s.open;
        var x = s.high, p = s.low, s = s.close;
        if (typeof k === "number")i.push(k); else if (k === null)i.hasNulls = !0;
        if (typeof x === "number")l.push(x); else if (x === null)l.hasNulls = !0;
        if (typeof p === "number")o.push(p);
        else if (p === null)o.hasNulls = !0;
        if (typeof s === "number")q.push(s); else if (s === null)q.hasNulls = !0
      } else if (typeof k === "number")i.push(k); else if (k === null)i.hasNulls = !0
    }
    return[g, h]
  };
  C.processData = function () {
    var a = this.options, b = a.dataGrouping, c = b && b.enabled, d = this.groupedData, e;
    this.forceCrop = c;
    if (cd.apply(this, arguments) !== !1 && c) {
      q(d || [], function (a, b) {
        a && (d[b] = a.destroy ? a.destroy() : null)
      });
      var f;
      f = this.chart;
      var c = this.processedXData, g = this.processedYData, h = f.plotSizeX, j = this.xAxis, k = r(j.groupPixelWidth,
        b.groupPixelWidth), i = c.length, m = f.series, l = this.pointRange;
      if (!j.groupPixelWidth) {
        for (f = m.length; f--;)m[f].xAxis === j && m[f].options.dataGrouping && (k = O(k, m[f].options.dataGrouping.groupPixelWidth));
        j.groupPixelWidth = k
      }
      if (i > h / k || b.forced) {
        e = !0;
        this.points = null;
        f = j.getExtremes();
        i = f.min;
        m = f.max;
        f = j.getGroupIntervalFactor && j.getGroupIntervalFactor(i, m, c) || 1;
        h = k * (m - i) / h * f;
        j = (j.getNonLinearTimeTicks || $b)(zc(h, b.units || Uc), i, m, null, c, this.closestPointRange);
        g = C.groupData.apply(this, [c, g, j, b.approximation]);
        c = g[0];
        g = g[1];
        if (b.smoothed) {
          f = c.length - 1;
          for (c[f] = m; f-- && f > 0;)c[f] += h / 2;
          c[0] = i
        }
        this.currentDataGrouping = j.info;
        if (a.pointRange === null)this.pointRange = j.info.totalRange;
        this.closestPointRange = j.info.totalRange;
        this.processedXData = c;
        this.processedYData = g
      } else this.currentDataGrouping = null, this.pointRange = l;
      this.hasGroupedData = e
    }
  };
  C.generatePoints = function () {
    dd.apply(this);
    this.groupedData = this.hasGroupedData ? this.points : null
  };
  C.tooltipHeaderFormatter = function (a) {
    var b = this.tooltipOptions, c = this.options.dataGrouping,
      d = b.xDateFormat, e, f = this.xAxis, g, h;
    if (f && f.options.type === "datetime" && c) {
      g = this.currentDataGrouping;
      c = c.dateTimeLabelFormats;
      if (g)f = c[g.unitName], g.count === 1 ? d = f[0] : (d = f[1], e = f[2]); else if (!d)for (h in K)if (K[h] >= f.closestPointRange) {
        d = c[h][0];
        break
      }
      d = Bb(d, a);
      e && (d += Bb(e, a + g.totalRange - 1));
      a = b.headerFormat.replace("{point.key}", d)
    } else a = fd.apply(this, [a]);
    return a
  };
  C.destroy = function () {
    for (var a = this.groupedData || [], b = a.length; b--;)a[b] && a[b].destroy();
    ed.apply(this)
  };
  J.line.dataGrouping = J.spline.dataGrouping =
    J.area.dataGrouping = J.areaspline.dataGrouping = w;
  J.column.dataGrouping = I(w, {approximation:"sum", groupPixelWidth:10});
  J.ohlc = I(J.column, {lineWidth:1, dataGrouping:{approximation:"ohlc", enabled:!0, groupPixelWidth:5}, tooltip:{pointFormat:'<span style="color:{series.color};font-weight:bold">{series.name}</span><br/>Open: {point.open}<br/>High: {point.high}<br/>Low: {point.low}<br/>Close: {point.close}<br/>'}, states:{hover:{lineWidth:3}}, threshold:null});
  var w = ea(ab, {applyOptions:function (a) {
    var b = this.series,
      c = 0;
    if (typeof a === "object" && typeof a.length !== "number")G(this, a), this.options = a; else if (a.length) {
      if (a.length === 5) {
        if (typeof a[0] === "string")this.name = a[0]; else if (typeof a[0] === "number")this.x = a[0];
        c++
      }
      this.open = a[c++];
      this.high = a[c++];
      this.low = a[c++];
      this.close = a[c++]
    }
    this.y = this.high;
    if (this.x === D && b)this.x = b.autoIncrement();
    return this
  }}), yc = ea(ma.column, {type:"ohlc", valueCount:4, pointClass:w, pointAttrToOptions:{stroke:"color", "stroke-width":"lineWidth"}, translate:function () {
    var a = this.yAxis;
    ma.column.prototype.translate.apply(this);
    q(this.points, function (b) {
      if (b.open !== null)b.plotOpen = a.translate(b.open, 0, 1, 0, 1);
      if (b.close !== null)b.plotClose = a.translate(b.close, 0, 1, 0, 1)
    })
  }, drawPoints:function () {
    var a = this, b = a.chart, c, d, e, f, g, h, j, k;
    q(a.points, function (i) {
      if (i.plotY !== D)j = i.graphic, c = i.pointAttr[i.selected ? "selected" : ""], f = c["stroke-width"] % 2 / 2, k = x(i.plotX) + f, g = x(i.barW / 2), h = ["M", k, x(i.yBottom), "L", k, x(i.plotY)], i.open !== null && (d = x(i.plotOpen) + f, h.push("M", k, d, "L", k - g, d)), i.close !== null &&
        (e = x(i.plotClose) + f, h.push("M", k, e, "L", k + g, e)), j ? j.animate({d:h}) : i.graphic = b.renderer.path(h).attr(c).add(a.group)
    })
  }, animate:null});
  ma.ohlc = yc;
  J.candlestick = I(J.column, {dataGrouping:{approximation:"ohlc", enabled:!0}, lineColor:"black", lineWidth:1, states:{hover:{lineWidth:2}}, tooltip:J.ohlc.tooltip, threshold:null, upColor:"white"});
  w = ea(yc, {type:"candlestick", pointAttrToOptions:{fill:"color", stroke:"lineColor", "stroke-width":"lineWidth"}, getAttribs:function () {
    yc.prototype.getAttribs.apply(this, arguments);
    var a = this.options, b = a.states, a = a.upColor, c = I(this.pointAttr);
    c[""].fill = a;
    c.hover.fill = b.hover.upColor || a;
    c.select.fill = b.select.upColor || a;
    q(this.points, function (a) {
      if (a.open < a.close)a.pointAttr = c
    })
  }, drawPoints:function () {
    var a = this, b = a.chart, c, d, e, f, g, h, j, k, i, m;
    q(a.points, function (l) {
      k = l.graphic;
      if (l.plotY !== D)c = l.pointAttr[l.selected ? "selected" : ""], h = c["stroke-width"] % 2 / 2, j = x(l.plotX) + h, d = x(l.plotOpen) + h, e = x(l.plotClose) + h, f = va.min(d, e), g = va.max(d, e), m = x(l.barW / 2), i = ["M", j - m, g, "L", j - m, f, "L", j +
        m, f, "L", j + m, g, "L", j - m, g, "M", j, g, "L", j, x(l.yBottom), "M", j, f, "L", j, x(l.plotY), "Z"], k ? k.animate({d:i}) : l.graphic = b.renderer.path(i).attr(c).add(a.group)
    })
  }});
  ma.candlestick = w;
  var kc = Eb.prototype.symbols;
  J.flags = I(J.column, {dataGrouping:null, fillColor:"white", lineWidth:1, pointRange:0, shape:"flag", stackDistance:7, states:{hover:{lineColor:"black", fillColor:"#FCFFC5"}}, style:{fontSize:"11px", fontWeight:"bold", textAlign:"center"}, threshold:null, y:-30});
  ma.flags = ea(ma.column, {type:"flags", sorted:!1, noSharedTooltip:!0,
    init:ia.prototype.init, pointAttrToOptions:{fill:"fillColor", stroke:"color", "stroke-width":"lineWidth", r:"radius"}, translate:function () {
      ma.column.prototype.translate.apply(this);
      var a = this.chart, b = this.points, c = b.length - 1, d, e, f = this.options.onSeries, f = (d = f && a.get(f)) && d.options.step, g = d && d.points, h = g && g.length, j, k, i;
      if (d && d.visible && h) {
        k = g[h - 1].x;
        for (b.sort(function (a, b) {
          return a.x - b.x
        }); h-- && b[c];)if (d = b[c], j = g[h], j.x <= d.x && j.plotY !== D) {
          if (d.x <= k)d.plotY = j.plotY, j.x < d.x && !f && (i = g[h + 1]) && i.plotY !==
            D && (d.plotY += (d.x - j.x) / (i.x - j.x) * (i.plotY - j.plotY));
          c--;
          h++;
          if (c < 0)break
        }
      }
      q(b, function (c, d) {
        if (c.plotY === D)c.plotY = a.plotHeight;
        if ((e = b[d - 1]) && e.plotX === c.plotX) {
          if (e.stackIndex === D)e.stackIndex = 0;
          c.stackIndex = e.stackIndex + 1
        }
      })
    }, drawPoints:function () {
      var a, b = this.points, c = this.chart.renderer, d, e, f = this.options, g = f.y, h = f.shape, j, k, i, m, l = f.lineWidth % 2 / 2, o;
      for (k = b.length; k--;)if (i = b[k], d = i.plotX + l, a = i.stackIndex, e = i.plotY, e !== D && (e = i.plotY + g + l - (a !== D && a * f.stackDistance)), j = a ? D : i.plotX + l, o = a ? D : i.plotY,
        m = i.graphic, e !== D)a = i.pointAttr[i.selected ? "select" : ""], m ? m.attr({x:d, y:e, r:a.r, anchorX:j, anchorY:o}) : m = i.graphic = c.label(i.options.title || f.title || "A", d, e, h, j, o).css(I(f.style, i.style)).attr(a).attr({align:h === "flag" ? "left" : "center", width:f.width, height:f.height}).add(this.group).shadow(f.shadow), j = m.box, a = j.getBBox(), i.shapeArgs = G(a, {x:d - (h === "flag" ? 0 : j.attr("width") / 2), y:e}); else if (m)i.graphic = m.destroy()
    }, drawTracker:function () {
      ma.column.prototype.drawTracker.apply(this);
      q(this.points, function (a) {
        X(a.tracker.element,
          "mouseover", function () {
            a.graphic.toFront()
          })
      })
    }, tooltipFormatter:function (a) {
      return a.point.text
    }, animate:function () {
    }});
  kc.flag = function (a, b, c, d, e) {
    var f = e && e.anchorX || a, e = e && e.anchorY || b;
    return["M", f, e, "L", a, b + d, a, b, a + c, b, a + c, b + d, a, b + d, "M", f, e, "Z"]
  };
  q(["circle", "square"], function (a) {
    kc[a + "pin"] = function (b, c, d, e, f) {
      var g = f && f.anchorX, f = f && f.anchorY, b = kc[a](b, c, d, e);
      g && f && b.push("M", g, c + e, "L", g, f);
      return b
    }
  });
  Sb === mb && q(["flag", "circlepin", "squarepin"], function (a) {
    mb.prototype.symbols[a] = kc[a]
  });
  var lc = Fa ? "touchstart" : "mousedown", Vc = Fa ? "touchmove" : "mousemove", Wc = Fa ? "touchend" : "mouseup", w = Ja("linearGradient", {x1:0, y1:0, x2:0, y2:1}, "stops", [
    [0, "#FFF"],
    [1, "#CCC"]
  ]), V = [].concat(Uc);
  V[4] = [P, [1, 2, 3, 4]];
  V[5] = [Ca, [1, 2, 3]];
  G(ja, {navigator:{handles:{backgroundColor:"#FFF", borderColor:"#666"}, height:40, margin:10, maskFill:"rgba(255, 255, 255, 0.75)", outlineColor:"#444", outlineWidth:1, series:{type:"areaspline", color:"#4572A7", compare:null, fillOpacity:0.4, dataGrouping:{approximation:"average", groupPixelWidth:2,
    smoothed:!0, units:V}, dataLabels:{enabled:!1}, id:gb + "navigator-series", lineColor:"#4572A7", lineWidth:1, marker:{enabled:!1}, pointRange:0, shadow:!1}, xAxis:{tickWidth:0, lineWidth:0, gridLineWidth:1, tickPixelInterval:200, labels:{align:"left", x:3, y:-4}}, yAxis:{gridLineWidth:0, startOnTick:!1, endOnTick:!1, minPadding:0.1, maxPadding:0.1, labels:{enabled:!1}, title:{text:null}, tickWidth:0}}, scrollbar:{height:Fa ? 20 : 14, barBackgroundColor:w, barBorderRadius:2, barBorderWidth:1, barBorderColor:"#666", buttonArrowColor:"#666",
    buttonBackgroundColor:w, buttonBorderColor:"#666", buttonBorderRadius:2, buttonBorderWidth:1, rifleColor:"#666", trackBackgroundColor:Ja("linearGradient", {x1:0, y1:0, x2:0, y2:1}, "stops", [
      [0, "#EEE"],
      [1, "#FFF"]
    ]), trackBorderColor:"#CCC", trackBorderWidth:1}});
  Highcharts.Scroller = function (a) {
    function b(a, b) {
      var c = {fill:U.backgroundColor, stroke:U.borderColor, "stroke-width":1}, d;
      ia || (ja[b] = j.g().css({cursor:"e-resize"}).attr({zIndex:4 - b}).add(), d = j.rect(-4.5, 0, 9, 16, 3, 1).attr(c).add(ja[b]), ra.push(d), d = j.path(["M",
        -1.5, 4, "L", -1.5, 12, "M", 0.5, 4, "L", 0.5, 12]).attr(c).add(ja[b]), ra.push(d));
      ja[b].translate(V + B + parseInt(a, 10), P + J / 2 - 8)
    }

    function c(a) {
      var b;
      ia || (pa[a] = j.g().add(fa), b = j.rect(-0.5, -0.5, B + 1, B + 1, v.buttonBorderRadius, v.buttonBorderWidth).attr({stroke:v.buttonBorderColor, "stroke-width":v.buttonBorderWidth, fill:v.buttonBackgroundColor}).add(pa[a]), ra.push(b), b = j.path(["M", B / 2 + (a ? -1 : 1), B / 2 - 3, "L", B / 2 + (a ? -1 : 1), B / 2 + 3, B / 2 + (a ? 2 : -2), B / 2]).attr({fill:v.buttonArrowColor}).add(pa[a]), ra.push(b));
      a && pa[a].attr({translateX:ba -
        B})
    }

    function d(d, e, f, g) {
      if (!isNaN(d)) {
        var h = v.barBorderWidth;
        aa = P + H;
        l = r(F.left, a.plotLeft + B);
        o = r(F.len, a.plotWidth - 2 * B);
        V = l - B;
        ba = o + 2 * B;
        if (F.getExtremes) {
          var k = a.xAxis[0].getExtremes(), p = k.dataMin === null, q = F.getExtremes(), t = wa(k.dataMin, q.dataMin), k = O(k.dataMax, q.dataMax);
          !p && (t !== q.min || k !== q.max) && F.setExtremes(t, k, !0, !1)
        }
        f = r(f, F.translate(d));
        g = r(g, F.translate(e));
        y = Z(wa(f, g));
        G = Z(O(f, g));
        C = G - y;
        if (!ia && (m && (la = j.rect().attr({fill:i.maskFill, zIndex:3}).add(), ma = j.rect().attr({fill:i.maskFill, zIndex:3}).add(),
          oa = j.path().attr({"stroke-width":$, stroke:i.outlineColor, zIndex:3}).add()), s))fa = j.g().add(), d = v.trackBorderWidth, n = j.rect().attr({y:-d % 2 / 2, fill:v.trackBackgroundColor, stroke:v.trackBorderColor, "stroke-width":d, r:v.trackBorderRadius || 0, height:B}).add(fa), sa = j.rect().attr({y:-h % 2 / 2, height:B, fill:v.barBackgroundColor, stroke:v.barBorderColor, "stroke-width":h, r:ea}).add(fa), ta = j.path().attr({stroke:v.rifleColor, "stroke-width":1}).add(fa);
        m && (la.attr({x:l, y:P, width:y, height:J}), ma.attr({x:l + G, y:P, width:o -
          G, height:J}), oa.attr({d:[ya, V, aa, ka, l + y + H, aa, l + y + H, aa + W - B, ya, l + G - H, aa + W - B, ka, l + G - H, aa, V + ba, aa]}), b(y + H, 0), b(G + H, 1));
        s && (c(0), c(1), fa.translate(V, x(aa + J)), n.attr({width:ba}), sa.attr({x:x(B + y) + h % 2 / 2, width:C - h}), h = B + y + C / 2 - 0.5, ta.attr({d:[ya, h - 3, B / 4, ka, h - 3, 2 * B / 3, ya, h, B / 4, ka, h, 2 * B / 3, ya, h + 3, B / 4, ka, h + 3, 2 * B / 3], visibility:C > 12 ? $a : Xa}));
        ia = !0
      }
    }

    function e(b) {
      var b = a.tracker.normalizeMouseEvent(b), c = b.chartX, d = b.chartY, b = Fa ? 10 : 7;
      if (d > P && d < P + J + B)(d = !s || d < P + J) && va.abs(c - y - l) < b ? (w = !0, M = G) : d && va.abs(c - G - l) < b ? (p =
        !0, M = y) : c > l + y && c < l + G ? (A = c, S = K.cursor, K.cursor = "ew-resize", D = c - y) : c > V && c < V + ba && (c = d ? c - l - C / 2 : c < l ? y - wa(10, C) : c > V + ba - B ? y + wa(10, C) : c < l + y ? y - C : G, c < 0 ? c = 0 : c + C > o && (c = o - C), c !== y && a.xAxis[0].setExtremes(F.translate(c, !0), F.translate(c + C, !0), !0, !1))
    }

    function f(b) {
      b = a.tracker.normalizeMouseEvent(b);
      b = b.chartX;
      b < l ? b = l : b > V + ba - B && (b = V + ba - B);
      w ? (N = !0, d(0, 0, b - l, M)) : p ? (N = !0, d(0, 0, M, b - l)) : A && (N = !0, b < D ? b = D : b > o + D - C && (b = o + D - C), d(0, 0, b - D, b - D + C))
    }

    function g() {
      N && a.xAxis[0].setExtremes(F.translate(y, !0), F.translate(G, !0), !0,
        !1);
      w = p = A = N = D = null;
      K.cursor = S
    }

    function h() {
      var b = da.xAxis, c = b.getExtremes(), e = c.min, f = c.max, g = c.dataMin, c = c.dataMax, h = f - e, j, i, k, l, m;
      j = t.xData;
      var n = !!b.setExtremes;
      i = f >= j[j.length - 1];
      j = e <= g;
      if (!u)t.options.pointStart = da.xData[0], t.setData(da.options.data, !1), m = !0;
      j && (l = g, k = l + h);
      i && (k = c, j || (l = O(k - h, t.xData[0])));
      n && (j || i) ? b.setExtremes(l, k, !0, !1) : (m && a.redraw(!1), d(O(e, g), wa(f, c)))
    }

    var j = a.renderer, k = a.options, i = k.navigator, m = i.enabled, l, o, t, u, v = k.scrollbar, s = v.enabled, w, p, A, M, D, N, F, ga, y, G, C, K = document.body.style,
      S, U = i.handles, J = m ? i.height : 0, $ = i.outlineWidth, B = s ? v.height : 0, W = J + B, ea = v.barBorderRadius, P, H = $ / 2, aa, V, ba, ia, xa = i.baseSeries, da = a.series[xa] || typeof xa === "string" && a.get(xa) || a.series[0], la, ma, oa, ja = [], fa, n, sa, ta, pa = [], ra = [];
    a.resetZoomEnabled = !1;
    (function () {
      var b = a.xAxis.length, c = a.yAxis.length, d = a.setSize;
      a.extraBottomMargin = W + i.margin;
      P = i.top || a.chartHeight - J - B - k.chart.spacingBottom;
      if (m) {
        var j = da.options, l = j.data, n = i.series;
        u = n.data;
        j.data = n.data = null;
        F = new a.Axis(I({ordinal:da.xAxis.options.ordinal},
          i.xAxis, {isX:!0, type:"datetime", index:b, height:J, top:P, offset:0, offsetLeft:B, offsetRight:-B, startOnTick:!1, endOnTick:!1, minPadding:0, maxPadding:0, zoomEnabled:!1}));
        ga = new a.Axis(I(i.yAxis, {alignTicks:!1, height:J, top:P, offset:0, index:c, zoomEnabled:!1}));
        b = I(da.options, n, {threshold:null, clip:!1, enableMouseTracking:!1, group:"nav", padXAxis:!1, xAxis:b, yAxis:c, name:"Navigator", showInLegend:!1, isInternal:!0, visible:!0});
        j.data = l;
        n.data = u;
        b.data = u || l;
        t = a.initSeries(b);
        X(da, "updatedData", h)
      } else F = {translate:function (b, c) {
        var d = a.xAxis[0].getExtremes(), e = a.plotWidth - 2 * B, f = d.dataMin, d = d.dataMax - f;
        return c ? b * d / e + f : e * (b - f) / d
      }};
      a.setSize = function (b, c, e) {
        F.options.top = ga.options.top = P = i.top || c - J - B - k.chart.spacingBottom;
        d.call(a, b, c, e)
      };
      X(a.container, lc, e);
      X(a.container, Vc, f);
      X(document, Wc, g)
    })();
    return{render:d, destroy:function () {
      ua(a.container, lc, e);
      ua(a.container, Vc, f);
      ua(document, Wc, g);
      m && ua(da, "updatedData", h);
      q([F, ga, la, ma, oa, n, sa, ta, fa], function (a) {
        a && a.destroy && a.destroy()
      });
      F = ga = la = ma = oa = n = sa = ta = fa = null;
      q([pa,
        ja, ra], function (a) {
        Ab(a)
      })
    }, series:t, xAxis:F, yAxis:ga}
  };
  G(ja, {rangeSelector:{buttonTheme:{width:28, height:16, padding:1, r:0, zIndex:10}}});
  ja.lang = I(ja.lang, {rangeSelectorZoom:"Zoom", rangeSelectorFrom:"From:", rangeSelectorTo:"To:"});
  Highcharts.RangeSelector = function (a) {
    function b(b, c, d) {
      var e = a.xAxis[0], f = e && e.getExtremes(), g = a.scroller && a.scroller.xAxis, h = (g = g && g.getExtremes && g.getExtremes()) && g.dataMax, j = f && f.dataMin, i = f && f.dataMax, g = wa(j, r(g && g.dataMin, j)), h = O(i, r(h, i)), k, l = e && wa(f.max, h), f = new Date(l),
        i = c.type, j = c.count, m, o, p = {millisecond:1, second:1E3, minute:6E4, hour:36E5, day:864E5, week:6048E5};
      if (!(g === null || h === null || b === u))p[i] ? (m = p[i] * j, k = O(l - m, g)) : i === "month" ? (f.setMonth(f.getMonth() - j), k = O(f.getTime(), g), m = 2592E6 * j) : i === "ytd" ? (f = new Date(0), i = new Date(h), o = i.getFullYear(), f.setFullYear(o), String(o) !== Bb("%Y", f) && f.setFullYear(o - 1), k = o = O(g || 0, f.getTime()), i = i.getTime(), l = wa(h || i, i)) : i === "year" ? (f.setFullYear(f.getFullYear() - j), k = O(g, f.getTime()), m = 31536E6 * j) : i === "all" && e && (k = g, l = h), s[b] &&
        s[b].setState(2), e ? setTimeout(function () {
        e.setExtremes(k, l, r(d, 1), 0, {rangeSelectorButton:c});
        u = b
      }, 1) : (g = a.options.xAxis, g[0] = I(g[0], {range:m, min:o}), u = b)
    }

    function c() {
      i && i.blur();
      m && m.blur()
    }

    function d(a, b) {
      var c = a.hasFocus ? p.inputEditDateFormat || "%Y-%m-%d" : p.inputDateFormat || "%b %e, %Y";
      if (b)a.HCTime = b;
      a.value = Bb(c, a.HCTime)
    }

    function e(b) {
      var c = b === "min", e;
      l[b] = da("span", {innerHTML:j[c ? "rangeSelectorFrom" : "rangeSelectorTo"]}, p.labelStyle, k);
      e = da("input", {name:b, className:gb + "range-selector", type:"text"},
        G({width:"80px", height:"16px", border:"1px solid silver", marginLeft:"5px", marginRight:c ? "5px" : "0", textAlign:"center"}, p.inputStyle), k);
      e.onfocus = e.onblur = function (a) {
        a = a || window.event;
        e.hasFocus = a.type === "focus";
        d(e)
      };
      e.onchange = function () {
        var b = e.value, d = Date.parse(b), f = a.xAxis[0].getExtremes();
        isNaN(d) && (d = b.split("-"), d = Date.UTC(Z(d[0]), Z(d[1]) - 1, Z(d[2])));
        if (!isNaN(d) && (c && d >= f.dataMin && d <= m.HCTime || !c && d <= f.dataMax && d >= i.HCTime))a.xAxis[0].setExtremes(c ? d : f.min, c ? f.max : d)
      };
      return e
    }

    var f = a.renderer,
      g, h = a.container, j = ja.lang, k, i, m, l = {}, o, t, u, v, s = [], x, p, w = [
        {type:"month", count:1, text:"1m"},
        {type:"month", count:3, text:"3m"},
        {type:"month", count:6, text:"6m"},
        {type:"ytd", text:"YTD"},
        {type:"year", count:1, text:"1y"},
        {type:"all", text:"All"}
      ];
    a.resetZoomEnabled = !1;
    (function () {
      a.extraTopMargin = 25;
      p = a.options.rangeSelector;
      x = p.buttons || w;
      var d = p.selected;
      X(h, lc, c);
      d !== D && x[d] && b(d, x[d], !1);
      X(a, "load", function () {
        X(a.xAxis[0], "afterSetExtremes", function () {
          this.isDirty && (s[u] && s[u].setState(0), u = null)
        })
      })
    })();
    return{render:function (c, l) {
      var r = a.options.chart.style, w = p.buttonTheme, A = p.inputEnabled !== !1, y = w && w.states, D = a.plotLeft, C;
      g || (v = f.text(j.rangeSelectorZoom, D, a.plotTop - 10).css(p.labelStyle).add(), C = D + v.getBBox().width + 5, q(x, function (c, d) {
        s[d] = f.button(c.text, C, a.plotTop - 25,function () {
          b(d, c);
          this.isActive = !0
        }, w, y && y.hover, y && y.select).css({textAlign:"center"}).add();
        C += s[d].width + (p.buttonSpacing || 0);
        u === d && s[d].setState(2)
      }), A && (t = k = da("div", null, {position:"relative", height:0, fontFamily:r.fontFamily,
        fontSize:r.fontSize, zIndex:1}), h.parentNode.insertBefore(k, h), o = k = da("div", null, G({position:"absolute", top:a.plotTop - 25 + "px", right:a.chartWidth - a.plotLeft - a.plotWidth + "px"}, p.inputBoxStyle), k), i = e("min"), m = e("max")));
      A && (d(i, c), d(m, l));
      g = !0
    }, destroy:function () {
      ua(h, lc, c);
      q([s], function (a) {
        Ab(a)
      });
      v && (v = v.destroy());
      if (i)i.onfocus = i.onblur = i.onchange = null;
      if (m)m.onfocus = m.onblur = m.onchange = null;
      q([i, m, l.min, l.max, o, t], function (a) {
        Nb(a)
      });
      i = m = l = k = o = t = null
    }}
  };
  ec.prototype.callbacks.push(function (a) {
    function b() {
      f =
        a.xAxis[0].getExtremes();
      g.render(O(f.min, f.dataMin), wa(f.max, f.dataMax))
    }

    function c() {
      f = a.xAxis[0].getExtremes();
      h.render(f.min, f.max)
    }

    function d(a) {
      g.render(a.min, a.max)
    }

    function e(a) {
      h.render(a.min, a.max)
    }

    var f, g = a.scroller, h = a.rangeSelector;
    g && (X(a.xAxis[0], "afterSetExtremes", d), X(a, "resize", b), b());
    h && (X(a.xAxis[0], "afterSetExtremes", e), X(a, "resize", c), c());
    X(a, "destroy", function () {
      g && (ua(a, "resize", b), ua(a.xAxis[0], "afterSetExtremes", d));
      h && (ua(a, "resize", c), ua(a.xAxis[0], "afterSetExtremes",
        e))
    })
  });
  Highcharts.StockChart = function (a, b) {
    var c = a.series, d, e = {marker:{enabled:!1, states:{hover:{enabled:!0, radius:5}}}, shadow:!1, states:{hover:{lineWidth:2}}, dataGrouping:{enabled:!0}};
    a.xAxis = Kb(zb(a.xAxis || {}), function (a) {
      return I({minPadding:0, maxPadding:0, ordinal:!0, title:{text:null}, showLastLabel:!0}, a, {type:"datetime", categories:null})
    });
    a.yAxis = Kb(zb(a.yAxis || {}), function (a) {
      d = a.opposite;
      return I({labels:{align:d ? "right" : "left", x:d ? -2 : 2, y:-2}, showLastLabel:!1, title:{text:null}}, a)
    });
    a.series =
      null;
    a = I({chart:{panning:!0}, navigator:{enabled:!0}, scrollbar:{enabled:!0}, rangeSelector:{enabled:!0}, title:{text:null}, tooltip:{shared:!0, crosshairs:!0}, legend:{enabled:!1}, plotOptions:{line:e, spline:e, area:e, areaspline:e, column:{shadow:!1, borderWidth:0, dataGrouping:{enabled:!0}}}}, a, {chart:{inverted:!1}});
    a.series = c;
    return new ec(a, b)
  };
  var gd = C.init, hd = C.processData, id = ab.prototype.tooltipFormatter;
  C.init = function () {
    gd.apply(this, arguments);
    var a = this.options.compare;
    if (a)this.modifyValue = function (b, c) {
      var d = this.compareValue, b = a === "value" ? b - d : b = 100 * (b / d) - 100;
      if (c)c.change = b;
      return b
    }
  };
  C.processData = function () {
    hd.apply(this, arguments);
    if (this.options.compare)for (var a = 0, b = this.processedXData, c = this.processedYData, d = c.length, e = this.xAxis.getExtremes().min; a < d; a++)if (typeof c[a] === "number" && b[a] >= e) {
      this.compareValue = c[a];
      break
    }
  };
  ab.prototype.tooltipFormatter = function (a) {
    a = a.replace("{point.change}", (this.change > 0 ? "+" : "") + Zb(this.change, this.series.tooltipOptions.changeDecimals || 2));
    return id.apply(this,
      [a])
  };
  (function () {
    var a = C.init, b = C.getSegments;
    C.init = function () {
      var b, d;
      a.apply(this, arguments);
      b = this.chart;
      (d = this.xAxis) && d.options.ordinal && X(this, "updatedData", function () {
        delete d.ordinalIndex
      });
      if (d && d.options.ordinal && !d.hasOrdinalExtension) {
        d.hasOrdinalExtension = !0;
        d.beforeSetTickPositions = function () {
          var a, b = [], c = !1, e, k = this.getExtremes(), i = k.min, k = k.max, m;
          if (this.options.ordinal) {
            q(this.series, function (c, d) {
              if (c.visible !== !1 && (b = b.concat(c.processedXData), a = b.length, d && a)) {
                b.sort(function (a, b) {
                  return a - b
                });
                for (d = a - 1; d--;)b[d] === b[d + 1] && b.splice(d, 1)
              }
            });
            a = b.length;
            if (a > 2) {
              e = b[1] - b[0];
              for (m = a - 1; m-- && !c;)b[m + 1] - b[m] !== e && (c = !0)
            }
            c ? (this.ordinalPositions = b, c = d.val2lin(i, !0), e = d.val2lin(k, !0), this.ordinalSlope = k = (k - i) / (e - c), this.ordinalOffset = i - c * k) : this.ordinalPositions = this.ordinalSlope = this.ordinalOffset = D
          }
        };
        d.val2lin = function (a, b) {
          var c = this.ordinalPositions;
          if (c) {
            var d = c.length, e, i;
            for (e = d; e--;)if (c[e] === a) {
              i = e;
              break
            }
            for (e = d - 1; e--;)if (a > c[e] || e === 0) {
              c = (a - c[e]) / (c[e + 1] - c[e]);
              i = e + c;
              break
            }
            return b ?
              i : this.ordinalSlope * (i || 0) + this.ordinalOffset
          } else return a
        };
        d.lin2val = function (a, b) {
          var c = this.ordinalPositions;
          if (c) {
            var d = this.ordinalSlope, e = this.ordinalOffset, i = c.length - 1, m, l;
            if (b)a < 0 ? a = c[0] : a > i ? a = c[i] : (i = La(a), l = a - i); else for (; i--;)if (m = d * i + e, a >= m) {
              d = d * (i + 1) + e;
              l = (a - m) / (d - m);
              break
            }
            return l !== D && c[i] !== D ? c[i] + (l ? l * (c[i + 1] - c[i]) : 0) : a
          } else return a
        };
        d.getExtendedPositions = function () {
          var a = d.series[0].currentDataGrouping, e = d.ordinalIndex, h = a ? a.count + a.unitName : "raw", j = d.getExtremes(), k, i;
          if (!e)e =
            d.ordinalIndex = {};
          if (!e[h])k = {series:[], getExtremes:function () {
            return{min:j.dataMin, max:j.dataMax}
          }, options:{ordinal:!0}}, q(d.series, function (d) {
            i = {xAxis:k, xData:d.xData, chart:b};
            i.options = {dataGrouping:a ? {enabled:!0, forced:!0, approximation:"open", units:[
              [a.unitName, [a.count]]
            ]} : {enabled:!1}};
            d.processData.apply(i);
            k.series.push(i)
          }), d.beforeSetTickPositions.apply(k), e[h] = k.ordinalPositions;
          return e[h]
        };
        d.getGroupIntervalFactor = function (a, b, c) {
          for (var d = 0, e = c.length, i = []; d < e - 1; d++)i[d] = c[d + 1] - c[d];
          i.sort(function (a, b) {
            return a - b
          });
          c = i[La(e / 2)];
          return e * c / (b - a)
        };
        d.postProcessTickInterval = function (a) {
          var b = this.ordinalSlope;
          return b ? a / (b / d.closestPointRange) : a
        };
        d.getNonLinearTimeTicks = function (a, b, c, e, k, i, m) {
          var l = 0, o = 0, q, r = {}, v, s, w, p = [], x = d.options.tickPixelInterval;
          if (!k || b === D)return $b(a, b, c, e);
          for (s = k.length; o < s; o++) {
            w = o && k[o - 1] > c;
            k[o] < b && (l = o);
            if (o === s - 1 || k[o + 1] - k[o] > i * 5 || w)q = $b(a, k[l], k[o], e), p = p.concat(q), l = o + 1;
            if (w)break
          }
          a = q.info;
          if (m && a.unitRange <= K[db]) {
            o = p.length - 1;
            for (l = 1; l < o; l++)(new Date(p[l]))[eb]() !==
              (new Date(p[l - 1]))[eb]() && (r[p[l]] = P, v = !0);
            v && (r[p[0]] = P);
            a.higherRanks = r
          }
          p.info = a;
          if (m && A(x)) {
            var m = a = p.length, o = [], C;
            for (v = []; m--;)l = d.translate(p[m]), C && (v[m] = C - l), o[m] = C = l;
            v.sort();
            v = v[La(v.length / 2)];
            v < x * 0.6 && (v = null);
            m = p[a - 1] > c ? a - 1 : a;
            for (C = void 0; m--;)l = o[m], c = C - l, C && c < x * 0.8 && (v === null || c < v * 0.8) ? (r[p[m]] && !r[p[m + 1]] ? (c = m + 1, C = l) : c = m, p.splice(c, 1)) : C = l
          }
          return p
        };
        var e = b.pan;
        b.pan = function (a) {
          var d = b.xAxis[0], h = !1;
          if (d.options.ordinal) {
            var j = b.mouseDownX, k = d.getExtremes(), i = k.dataMax, m = k.min, l =
              k.max, o;
            o = b.hoverPoints;
            var r = d.closestPointRange, j = (j - a) / (d.translationSlope * (d.ordinalSlope || r)), u = {ordinalPositions:d.getExtendedPositions()}, v, r = d.lin2val, s = d.val2lin;
            if (u.ordinalPositions) {
              if (Ga(j) > 1)o && q(o, function (a) {
                a.setState()
              }), j < 0 ? (o = u, u = d.ordinalPositions ? d : u) : o = d.ordinalPositions ? d : u, v = u.ordinalPositions, i > v[v.length - 1] && v.push(i), o = r.apply(o, [s.apply(o, [m, !0]) + j, !0]), j = r.apply(u, [s.apply(u, [l, !0]) + j, !0]), o > wa(k.dataMin, m) && j < O(i, l) && d.setExtremes(o, j, !0, !1), b.mouseDownX = a, W(b.container,
                {cursor:"move"})
            } else h = !0
          } else h = !0;
          h && e.apply(b, arguments)
        }
      }
    };
    C.getSegments = function () {
      var a = this, d, e = a.options.gapSize;
      b.apply(a);
      if (a.xAxis.options.ordinal && e)d = a.segments, q(d, function (b, g) {
        for (var h = b.length - 1; h--;)b[h + 1].x - b[h].x > a.xAxis.closestPointRange * e && d.splice(g + 1, 0, b.splice(h + 1, b.length - h))
      })
    }
  })();
  G(Highcharts, {Chart:ec, dateFormat:Bb, pathAnim:Xb, getOptions:function () {
    return ja
  }, hasBidiBug:bd, numberFormat:Zb, Point:ab, Color:oa, Renderer:Sb, SVGRenderer:Eb, VMLRenderer:mb, CanVGRenderer:xc,
    seriesTypes:ma, setOptions:function (a) {
      hc = I(hc, a.xAxis);
      tc = I(tc, a.yAxis);
      a.xAxis = a.yAxis = D;
      ja = I(ja, a);
      Gc();
      return ja
    }, Series:ia, addEvent:X, removeEvent:ua, createElement:da, discardElement:Nb, css:W, each:q, extend:G, map:Kb, merge:I, pick:r, splat:zb, extendClass:ea, placeBox:Fc, product:"Highstock", version:"1.1.5"})
})();
