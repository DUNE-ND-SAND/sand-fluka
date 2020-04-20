
RC     := root-config
ifeq ($(findstring $(MAKECMDTARGET),clean),)
ifeq ($(shell which $(RC) 2>&1 | sed -ne "s@.*/$(RC)@$(RC)@p"),$(RC))
MKARCH := $(wildcard $(shell $(RC) --etcdir)/Makefile.arch)
RCONFIG := $(wildcard $(shell $(RC) --incdir)/RConfigure.h)
endif
ifneq ($(MKARCH),)
include $(MKARCH)
else
ifeq ($(ROOTSYS),)
ROOTSYS = ..
endif
include $(ROOTSYS)/etc/Makefile.arch
endif
endif
# Tutorials dir needed by stressProof
ifneq ($(RCONFIG),)
TUTDIR := $(wildcard $(shell grep ROOTDOCDIR $(RCONFIG) | sed "s|.*\"\(.*\)\"|\1|")/tutorials)
endif
ifeq ($(TUTDIR),)
ifeq ($(ROOTSYS),)
ROOTSYS = ..
endif
TUTDIR := $(ROOTSYS)/tutorials
endif
-include ../MyConfig.mk

#------------------------------------------------------------------------------

LIBS += -lEG

VPATH 		 =../src/

TG4EVENTO        = TG4Event.$(ObjSuf) TG4EventDict.$(ObjSuf)
TG4EVENTS        = TG4Event.$(SrcSuf) TG4EventDict.$(SrcSuf)
TG4EVENTSO       = TG4Event.$(DllSuf)
MAIN             = Main$(ExeSuf)

TG4EVENTLIB      = $(shell pwd)/$(TG4EVENTSO)

MAINWRITEO       = MainWrite.$(ObjSuf)
MAINWRITES       = MainWrite.$(SrcSuf)

TG4TRAJO         =TG4Trajectory.$(ObjSuf)
TG4TRAJS         =TG4Trajectory.$(SrcSuf)

TG4HITSEGO       =TG4HitSegment.$(ObjSuf)
TG4HITSEGS       =TG4HitSegment.$(SrcSuf)

TG4PRIMO         =TG4PrimaryVertex.$(ObjSuf)
TG4PRIMS         =TG4PrimaryVertex.$(SrcSuf)

MAPO       =MapGeometry.$(ObjSuf)
MAPS       =MapGeometry.$(SrcSuf)



OBJS          = $(TG4EVENTO) $(MAINWRITEO) $(TG4TRAJO) $(TG4HITSEGO) $(TG4PRIMO) $(MAPO)
PROGRAMS      = $(MAIN) $(TG4EVENTSO)



#------------------------------------------------------------------------------

.SUFFIXES: .$(SrcSuf) .$(ObjSuf) .$(DllSuf)

all:            $(PROGRAMS) 

$(TG4EVENTSO):  $(TG4EVENTO) $(TG4TRAJO) $(TG4HITSEGO) $(TG4PRIMO)
		$(LD) $(SOFLAGS) $(LDFLAGS) $^ $(OutPutOpt) $@ $(EXPLLINKLIBS)  
		@echo "$@ done"


$(MAIN):        $(OBJS)
		$(LD) $(LDFLAGS) $^ $(LIBS) $(OutPutOpt)$@
		$(MT_EXE)
		@echo "$@ done"


clean:      
	@rm -f $(PROGRAMS) $(TG4EVENTSO) $(TG4EVENTLIB) $(OBJS) *Dict.* *.def *.exp \
	.root *.ps *.so *.lib *.dll *.d *.log .def so_locations \
	files/* *.pcm testdb.sqlite
	@rm -rf cxx_repository

.SUFFIXES: .$(SrcSuf)

###

#TG4Event.$(ObjSuf): TG4Event.h  TG4PrimaryVertex.h TG4Trajectory.h TG4HitSegment.h
TG4Event.$(ObjSuf): TG4Event.h  
MainWrite.$(ObjSuf): TG4Event.h  TG4PrimaryVertex.h TG4Trajectory.h TG4HitSegment.h

TG4Prim.$(ObjSuf): TG4PrimaryVertex.h
TG4Traj.$(ObjSuf): TG4Trajectory.h
TG4HitSegment.$(ObjSuf): TG4HitSegment.h
MapGeometry.$(ObjSuf): MapGeometry.h



TG4EventDict.$(SrcSuf): TG4Event.h  TG4PrimaryVertex.h TG4Trajectory.h TG4HitSegment.h edepsim_io_LinkDef.h
	@echo "Generating dictionary $@..."
	$(ROOTCLING) -f $@ -c $^


.$(SrcSuf).$(ObjSuf):
	$(CXX)  $(CXXFLAGS) -c $<

