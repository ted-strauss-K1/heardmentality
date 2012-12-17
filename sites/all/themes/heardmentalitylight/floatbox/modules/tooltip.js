/* Floatbox v4.18 */
(function(){var a=true,b=false,c=null;fb.extend(fb.proto,{GM:function(){var d=this;d.IN=50;d.IO=d.IN*0.001;d.IP=0;d.JZ=d.KA=d.FL=d.FM=d.JJ=-1;d.target=c;d.GK=function(f){d.JZ=f.clientX+d.dx;d.KA=f.clientY+d.dy;d.target=f.target;if(d.FL===-1){d.FL=d.JZ}if(d.FM===-1){d.FM=d.KA}if(typeof d.FO===fb.RW){d.FO()}};if(fb.ie){d.mousemoveHash=fb.DU(d.GK)}d.IL=function(){var f=d.JZ-d.FL,e=d.KA-d.FM;d.JJ=Math.sqrt(f*f+e*e)/d.IO;d.FL=d.JZ;d.FM=d.KA;d.IP+=d.IN;if(d.IP&&typeof d.IM===fb.RW){d.IM()}};d.JN=function(h){d.F=h||document;var g=fb.DJ(d.F[fb.QH]||d.F[fb.UB]);if(g){var f=fb[fb.SF](g),e=fb[fb.SH](fb.Z);d.dx=f.left-e.left;d.dy=f.top-e.top}else{d.dx=d.dy=0}fb[fb.PC](d.F,fb.TB,d.GK,d.mousemoveHash)};d.JU=function(){fb[fb.UJ](d.F,fb.TB,d.GK,d.mousemoveHash);d.FO=c};d.JO=function(){d.IP=-d.IN;d.FL=d.FM=d.JJ=-1;d.EX=setInterval(d.IL,d.IN);d.IL()};d.JV=function(){clearInterval(d.EX);d.IM=c}},KD:function(k,n){var u=this,s={doAnimations:b,color:"white",scrolling:"no",roundCorners:"all",cornerRadius:4,shadowType:"drop",shadowSize:4,showClose:b,titleAsCaption:b,enableKeyboardNav:b,padding:0,outerBorder:1,innerBorder:0,enableDragResize:b,enableDragMove:b,centerOnResize:b,attachToHost:b,moveWithMouse:b,placeAbove:b,timeout:0,delay:80,mouseSpeed:120,fadeDuration:3,defaultCursor:b,FC:a};function q(){var t=fb.KH,j=t.W,y=t.mo,x=u[fb.SF](t.node),i=u[fb.SH](u.Z);y.JV();v();if(j.attachToHost){y.JU();j.EE=x.height;j.boxTop=x.top-i.top+(j[fb.UT]==="halo"?j[fb.US]:0)}else{t.hostLeft=x.left-i.left;t.EH=x.top-i.top;t.hostRight=t.hostLeft+x.width;t.ED=t.EH+x.height;j.EE=u.O(j[fb.US]+1,u.ie?19:21);j.boxTop=y.KA;if(j.placeAbove){j.boxTop-=5}}if(j.moveWithMouse){t.JQ=y.JZ;t.JR=y.KA;t.FK=j.disableScroll?i:{left:0,top:0};y.FO=function(){if(!fb.KH){return}if(fb.AA){if(y.JZ<t.hostLeft||y.JZ>t.hostRight||y.KA<t.EH||y.KA>t.ED){w()}else{if(fb.AA.fbBox&&typeof t.AT==="number"){var z=fb.AA.fbBox.style;z.left=(t.AT+y.JZ-t.JQ-t.FK.left)+"px";z.top=(t.AU+y.KA-t.JR-t.FK.top)+"px";if(j.disableScroll){t.FK=u[fb.SH](u.Z)}}}}}}u.start(c,j);if(j[fb.VG]){if(t.KC){clearTimeout(t.KC)}t.KC=u.G(function(){t.KC=c;w()},j[fb.VG]*1000)}}function w(){if(!fb.KH){return}var i=fb.KH;i.mo.JV();i.mo.JU();clearTimeout(i.KC);fb.KH=i.AT=i.AU=i.node.GP=c;if(fb.AA){if(u.EM){u.end(fb.AA.L)}else{u.U(fb.AA.fbBox,0,i.W.fadeDuration,function(){if(fb.AA){u.end(fb.AA.L)}})}}}function m(){u.D("ttEnd");if(fb.KH){u.V("ttEnd",w,50)}}function v(){u.D("ttEnd")}function p(z){this.GP=a;var x=fb.KE.length;while(x--){if(this===fb.KE[x].node){break}}if(x===-1){return}v();var t=fb.KE[x],y=t.mo,j=t.W;if(!fb.KH||this!==fb.KH.node){if(fb.AA){w()}fb.KH=t;clearInterval(y.EX);y.JN(t.F);y.GK(z);y.IM=function(){if(!fb.AA&&(!j.delay||(y.JJ<j.mouseSpeed&&y.IP>j.delay))){q()}};y.JO()}}function d(i){if(!this.GP&&this.GQ){this.GQ(i)}u[fb.UJ](this,fb.TB,d)}function r(i){if(fb.KH){m()}}u.extend(s,u.J.KI.tooltip,u.HL.KI.tooltip);var l=k.length;while(l--){var h=b,f=k[l],g=fb.KE.length;while(g--){if(fb.KE[g].node===f){h=a;break}}if(h){continue}var e=u.extend({},s),o={W:e,node:f,L:n};u.extend(e,u.HO(f[fb.RX]("data-fb-tooltip")));if(!e.source){continue}fb.KE.push(o);e[fb.UL]=0;e.modal=e.sameBox=b;if(e[fb.UN]===fb.TG){e[fb.QC]=0}if(e[fb.UT]===fb.TG){e[fb.US]=0}if(e[fb.US]>16){e[fb.US]=16}if(e.attachToHost||u.EY){e.moveWithMouse=b}e.disableScroll=!u.EK&&e.moveWithMouse;e.afterBoxStart=function(){var i=fb.AA.fbBox;i[fb.TQ]=v;i[fb.TP]=m;u.U(i,0)};e.afterItemStart=function(){u.U(fb.AA.fbBox,100,u.EM?0:e.fadeDuration)};if(e.defaultCursor){f.style.cursor="default"}f[fb.UH]("title");o.F=f[fb.TW];o.mo=o.F.GL||(o.F.GL=new u.GM);f.GQ=u[fb.PC](f,"mouseover",p,c,n);f.GK=u[fb.PC](f,fb.TB,d,c,n);f.GN=u[fb.PC](f,"mouseout",r,c,n)}},tooltipLoaded:a})})();