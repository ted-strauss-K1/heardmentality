/* Floatbox v4.18 */
fb.extend(fb.proto,{BY:function(f,c){var b=fb,e=b.E[f],a=e.GZ[c].img,d=a[fb.RX]("data-fb-src")||a[fb.RX]("longdesc");if(d&&d!=="done"){a.src=d;a[fb.UP]("data-fb-src","done")}},BZ:function(){var b=fb,a=b.E.length,d,c;while(a--){if((d=b.E[a])){c=d.showing+1;if(c>=d.GZ.length){c=0}b.BY(a,c);if(b.preloadAll&&fb.HV.count&&d.GZ[d.showing].href){b.G(function(){fb.preload(d.GZ[d.showing].href)},200)}}}},CA:function(g,n,s){var h=fb,j=h.E[g],d=j.GZ[j.showing],l=s?0:h.cycleFadeDuration*2;try{if(!(j&&d&&d[fb.TE])){return}}catch(q){return}if(n>=j.GZ.length){n=0}if(n<0){n=j.GZ.length-1}if(n===j.showing){return}var a=j.GZ[n],m=typeof j.previous==="number"?j.GZ[j.previous]:null,f=d.img,c=a.img,k=m&&m.img,i=d.span,b=a.span,p=m&&m.span,o=function(){h.U(f,0,l/1.3,function(){d.style[fb.QI]=fb.TG},null,"cycleThisImg"+g)},r=h.EM?function(){if(i){i.style[fb.VI]=fb.SK}if(b){b.style[fb.VI]=fb.VJ}}:null;h.D("fade_cycleThisImg"+g);h.D("fade_cycleNextImg"+g);h.D("fade_cycleThisSpan"+g);h.D("fade_cycleNextSpan"+g);h.U(f,100,0);h.U(k,0,0);h.U(c,0,0);if(h.EM){if(i){i.style[fb.VI]=fb.VJ}if(p){p.style[fb.VI]=fb.SK}if(b){b.style[fb.VI]=fb.SK}}else{h.U(i,100,0);h.U(p,0,0);h.U(b,0,0)}if(m){m.style[fb.QI]=fb.TG}d.style.zIndex="10";a.style.zIndex="20";a.style[fb.QI]=h.H(a)==="a"?fb.SR:"block";if(j.div[fb.TJ]<a[fb.TJ]){j.div.style.height=a[fb.TJ]+"px"}h.U(c,100,l,o,r,"cycleNextImg"+g);if(!h.EM){if(i){i.style.opacity="1";h.U(i,0,l,null,null,"cycleThisSpan"+g)}if(b){h.U(b,100,l,null,null,"cycleNextSpan"+g)}}j.previous=j.showing;j.showing=n;h.BZ()},CB:function(){var d=fb,e,a,b=fb[fb.SU].length,c=d.E.length;while(b--){if((a=fb[fb.SU][b])&&a.fbBox&&a.modal){break}}while(c--){if((e=d.E[c])&&e.L>=b&&!e.hovered){d.CA(c,e.showing+1)}}d.E.timer=d.G(d.CB,d.DH()*1000)},cycleGo:function(){var a=fb;a.cycleStop();a.E.timer=a.G(a.CB,a.DH()*600)},cycleStop:function(){var a=fb;clearTimeout(a.E.timer)},DH:function(){var b=fb,a=b.E.length,f,c;while(a--){try{if((f=b.E[a])&&(c=f.GZ[f.showing].EX)){if((c=b.DI(c))){return c}}}catch(d){}}return b.cycleInterval},BX:function(q,e){var m=fb,u=q.length;function h(){fb.E[this.idx].hovered=true}function l(){fb.E[this.idx].hovered=false}while(u--){var n=q[u],s=fb.E.length;while(s--){if(fb.E[s].div===n){fb.E.splice(s,1)}}var c=n.childNodes,d=[],f=0;for(var s=0;s<c.length;s++){var p=c[s],y=m.H(p);if(/^(a|div|img)$/.test(y)){if(y==="img"){var g=p[fb.TW][fb.QD]("div");p[fb.UA].replaceChild(g,p);g[fb.PG](p);p=g}var x=p[fb.SC]("img")[0];if(x){if(!d.length){p[fb.PT]+=" first-child"}x.style[fb.QI]=fb.SR;if(p[fb.TM]){f=d.length;if(n[fb.TJ]<p[fb.TJ]){n.style.height=p[fb.TJ]+"px"}}p.EX=m.HO(p[fb.RX]("data-fb-options")||p[fb.RX]("rev")||"").cycleInterval||m.HO(x[fb.RX]("data-fb-options")||x[fb.RX]("rev")||"").cycleInterval||null;p.img=x;p.span=p[fb.SC]("span")[0];d.push(p)}}}if(d.length>1){var b=n[fb.RX]("data-fb-options")||n[fb.RX]("rev"),o=(b&&m.HO(b).cyclePauseOnHover),s=d.length;if(typeof o!==fb.PP){o=m.cyclePauseOnHover}while(s--){var p=d[s];if(o){p.idx=fb.E.length;m[fb.PC](p,"mouseover",h,null,e);m[fb.PC](p,"mouseout",l,null,e)}if(m.H(d[s])==="a"){var r=m.anchors.length;while(r--){var w=m.anchors[r];if(p===w.B){var v=m.E.length;w.W.preloadCycleItem="fb.BY("+v+", "+s+")";w.W.setCycleItem="fb.CA("+v+", "+s+", true);";if(w.W[fb.PR]===m.undefined&&!(w.W.titleAsCaption&&w.AI)&&p.span){w.W[fb.PR]=p.span[fb.ST]}break}}}}m.E.push({GZ:d,showing:f,L:e,div:n})}}m.BZ();if(!m.KB.cycle){m.cycleGo()}},cyclerLoaded:true});