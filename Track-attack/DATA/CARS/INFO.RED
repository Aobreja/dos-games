axis 2
clearbuffer static_backdrop bpp\grid.bpp
palette car\cued.pal
scale 1
camera pos <0,0,6000> target <0,0,0> focal 31

light point <1000,1000,1000> <0,0,0>

sourcing_table data\light.tab

matdef "RSIDE RIGHT" SHADED TEXT data\cars\bpp\red0017.bpp
matdef "RSIDE LEFT" SHADED TEXT data\cars\bpp\red0018.bpp
matdef "RTYRE RING"      SHADED FLAT <4,4,4>
matdef "RRAM RACER WHEELS" TRANS SHADED TEXT data\cars\gaz\wheel3.bpp
matdef "RRAM RACER WHEELS I" TRANS SHADED TWOSIDE TEXT data\cars\gaz\wheel3.bpp
matdef "RWHEELARCH"      SHADED FLAT <16,16,16>
matdef "RBACK"           SHADED TEXT data\cars\bpp\red0006.bpp
matdef "RTAIL LIGHT"     SHADED TEXT data\cars\bpp\red0014.bpp
matdef "RBONNET"         SHADED TEXT data\cars\bpp\red0007.bpp
matdef "RNOSE"           SHADED TEXT data\cars\bpp\red0008.bpp
matdef "RUNDER CAR"      SHADED TEXT data\cars\bpp\red0019.bpp
matdef "RENGINE_TOP_1"   TRANS SHADED TWOSIDE TEXT data\cars\bpp\red0011.bpp
matdef "RENGINE_TOP_2"   TRANS SHADED TWOSIDE TEXT data\cars\bpp\blue0012.bpp
matdef "RENGINE_TOP_3"   TRANS SHADED TWOSIDE TEXT data\cars\bpp\blue0013.bpp
matdef "RENGINE BLOCK"   SHADED TEXT data\cars\bpp\red0010.bpp
matdef "RTOP (CAB)"      SHADED TEXT data\cars\bpp\red0005.bpp
matdef "RSUSSPENSION"    TWOSIDE TRANS SHADED TEXT data\cars\bpp\blue0009.bpp
matdef "RRAM BAR FRONT"  TWOSIDE TRANS SHADED TEXT data\cars\bpp\red0015.bpp
matdef "RRAM BAR BACK"   TWOSIDE TRANS SHADED TEXT data\cars\bpp\red0016.bpp
matdef "RTURBO_SCREEN"	 TWOSIDE TRANS TEXT data\cars\gaz\turbo3.bpp

matdef "BANG"	SHADED TEXT data\cars\bang.bpp

pf data\cars\car.red

