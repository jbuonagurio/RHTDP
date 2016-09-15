include $(MkInclude)

SOURCES = \
	compsn.f \
	comvel.f \
	disloc.f \
	frit94.f \
	frit94_iers.f \
	frmxyz.f \
	getbdy.f \
	getreg.f \
	grdamp.f \
	grdchk.f \
	grdvec.f \
	grdwei.f \
	initbd.f \
	initeq.f \
	initps.f \
	initvl.f \
	ipsgrd.f \
	iungrd.f \
	iymdmj.f \
	model.f \
	newcor.f \
	okada.f \
	okadaw.f \
	platvl.f \
	polyin.f \
	predv.f \
	psdisp.f \
	psgwei.f \
	radii.f \
	radr8t.f \
	setrf.f \
	settp.f \
	toit94.f \
	toit94_iers.f \
	tovneu.f \
	tovxyz.f \
	toxyz.f \
	vtranf.f \
	vtranf_iers.f \
	xto08.f

OBJECTS = $(SOURCES:.f=.o)

LIB_A = ../htdp.a

all: static
static: $(LIB_A)

$(LIB_A): $(OBJECTS)
	rm -f $(LIB_A)
	$(AR) -crs $(LIB_A) $(OBJECTS)
    
clean:
	rm -f $(OBJECTS) $(LIB_A)

# Dependencies
model.o: iymdmj.o getbdy.o
newcor.o: compsn.o radii.o
compsn.o: radr8t.o radii.o disloc.o psdisp.o
radr8t.o: radii.o
disloc.o: okada.o
okada.o: okadaw.o
psdisp.o: iymdmj.o grdchk.o psgwei.o grdamp.o
grdamp.o: ipsgrd.o
predv.o: toxyz.o xto08.o getreg.o comvel.o tovxyz.o vtranf.o vtranf_iers.o tovneu.o
xto08.o: toit94.o frit94.o toit94_iers.o frit94_iers.o frmxyz.o
getreg.o: polyin.o
comvel.o: toxyz.o platvl.o tovneu.o grdwei.o grdvec.o
platvl.o: vtranf.o
grdvec.o: iungrd.o

%.o: %.f
	$(FC) $(FFLAGS) -c $<
