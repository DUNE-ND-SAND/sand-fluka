// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME TG4EventDict
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// The generated code does not explicitly qualifies STL entities
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "TG4Event.h"
#include "TG4PrimaryVertex.h"
#include "TG4Trajectory.h"
#include "TG4HitSegment.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_TG4PrimaryVertex(void *p = 0);
   static void *newArray_TG4PrimaryVertex(Long_t size, void *p);
   static void delete_TG4PrimaryVertex(void *p);
   static void deleteArray_TG4PrimaryVertex(void *p);
   static void destruct_TG4PrimaryVertex(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TG4PrimaryVertex*)
   {
      ::TG4PrimaryVertex *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TG4PrimaryVertex >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TG4PrimaryVertex", ::TG4PrimaryVertex::Class_Version(), "TG4PrimaryVertex.h", 18,
                  typeid(::TG4PrimaryVertex), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TG4PrimaryVertex::Dictionary, isa_proxy, 4,
                  sizeof(::TG4PrimaryVertex) );
      instance.SetNew(&new_TG4PrimaryVertex);
      instance.SetNewArray(&newArray_TG4PrimaryVertex);
      instance.SetDelete(&delete_TG4PrimaryVertex);
      instance.SetDeleteArray(&deleteArray_TG4PrimaryVertex);
      instance.SetDestructor(&destruct_TG4PrimaryVertex);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TG4PrimaryVertex*)
   {
      return GenerateInitInstanceLocal((::TG4PrimaryVertex*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TG4PrimaryVertex*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TG4PrimaryParticle(void *p = 0);
   static void *newArray_TG4PrimaryParticle(Long_t size, void *p);
   static void delete_TG4PrimaryParticle(void *p);
   static void deleteArray_TG4PrimaryParticle(void *p);
   static void destruct_TG4PrimaryParticle(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TG4PrimaryParticle*)
   {
      ::TG4PrimaryParticle *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TG4PrimaryParticle >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TG4PrimaryParticle", ::TG4PrimaryParticle::Class_Version(), "TG4PrimaryVertex.h", 117,
                  typeid(::TG4PrimaryParticle), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TG4PrimaryParticle::Dictionary, isa_proxy, 4,
                  sizeof(::TG4PrimaryParticle) );
      instance.SetNew(&new_TG4PrimaryParticle);
      instance.SetNewArray(&newArray_TG4PrimaryParticle);
      instance.SetDelete(&delete_TG4PrimaryParticle);
      instance.SetDeleteArray(&deleteArray_TG4PrimaryParticle);
      instance.SetDestructor(&destruct_TG4PrimaryParticle);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TG4PrimaryParticle*)
   {
      return GenerateInitInstanceLocal((::TG4PrimaryParticle*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TG4PrimaryParticle*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TG4Trajectory(void *p = 0);
   static void *newArray_TG4Trajectory(Long_t size, void *p);
   static void delete_TG4Trajectory(void *p);
   static void deleteArray_TG4Trajectory(void *p);
   static void destruct_TG4Trajectory(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TG4Trajectory*)
   {
      ::TG4Trajectory *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TG4Trajectory >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TG4Trajectory", ::TG4Trajectory::Class_Version(), "TG4Trajectory.h", 26,
                  typeid(::TG4Trajectory), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TG4Trajectory::Dictionary, isa_proxy, 4,
                  sizeof(::TG4Trajectory) );
      instance.SetNew(&new_TG4Trajectory);
      instance.SetNewArray(&newArray_TG4Trajectory);
      instance.SetDelete(&delete_TG4Trajectory);
      instance.SetDeleteArray(&deleteArray_TG4Trajectory);
      instance.SetDestructor(&destruct_TG4Trajectory);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TG4Trajectory*)
   {
      return GenerateInitInstanceLocal((::TG4Trajectory*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TG4Trajectory*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TG4TrajectoryPoint(void *p = 0);
   static void *newArray_TG4TrajectoryPoint(Long_t size, void *p);
   static void delete_TG4TrajectoryPoint(void *p);
   static void deleteArray_TG4TrajectoryPoint(void *p);
   static void destruct_TG4TrajectoryPoint(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TG4TrajectoryPoint*)
   {
      ::TG4TrajectoryPoint *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TG4TrajectoryPoint >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TG4TrajectoryPoint", ::TG4TrajectoryPoint::Class_Version(), "TG4Trajectory.h", 94,
                  typeid(::TG4TrajectoryPoint), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TG4TrajectoryPoint::Dictionary, isa_proxy, 4,
                  sizeof(::TG4TrajectoryPoint) );
      instance.SetNew(&new_TG4TrajectoryPoint);
      instance.SetNewArray(&newArray_TG4TrajectoryPoint);
      instance.SetDelete(&delete_TG4TrajectoryPoint);
      instance.SetDeleteArray(&deleteArray_TG4TrajectoryPoint);
      instance.SetDestructor(&destruct_TG4TrajectoryPoint);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TG4TrajectoryPoint*)
   {
      return GenerateInitInstanceLocal((::TG4TrajectoryPoint*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TG4TrajectoryPoint*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TG4HitSegment(void *p = 0);
   static void *newArray_TG4HitSegment(Long_t size, void *p);
   static void delete_TG4HitSegment(void *p);
   static void deleteArray_TG4HitSegment(void *p);
   static void destruct_TG4HitSegment(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TG4HitSegment*)
   {
      ::TG4HitSegment *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TG4HitSegment >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TG4HitSegment", ::TG4HitSegment::Class_Version(), "TG4HitSegment.h", 28,
                  typeid(::TG4HitSegment), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TG4HitSegment::Dictionary, isa_proxy, 4,
                  sizeof(::TG4HitSegment) );
      instance.SetNew(&new_TG4HitSegment);
      instance.SetNewArray(&newArray_TG4HitSegment);
      instance.SetDelete(&delete_TG4HitSegment);
      instance.SetDeleteArray(&deleteArray_TG4HitSegment);
      instance.SetDestructor(&destruct_TG4HitSegment);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TG4HitSegment*)
   {
      return GenerateInitInstanceLocal((::TG4HitSegment*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TG4HitSegment*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TG4Event(void *p = 0);
   static void *newArray_TG4Event(Long_t size, void *p);
   static void delete_TG4Event(void *p);
   static void deleteArray_TG4Event(void *p);
   static void destruct_TG4Event(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TG4Event*)
   {
      ::TG4Event *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TG4Event >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TG4Event", ::TG4Event::Class_Version(), "TG4Event.h", 10,
                  typeid(::TG4Event), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TG4Event::Dictionary, isa_proxy, 4,
                  sizeof(::TG4Event) );
      instance.SetNew(&new_TG4Event);
      instance.SetNewArray(&newArray_TG4Event);
      instance.SetDelete(&delete_TG4Event);
      instance.SetDeleteArray(&deleteArray_TG4Event);
      instance.SetDestructor(&destruct_TG4Event);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TG4Event*)
   {
      return GenerateInitInstanceLocal((::TG4Event*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TG4Event*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr TG4PrimaryVertex::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TG4PrimaryVertex::Class_Name()
{
   return "TG4PrimaryVertex";
}

//______________________________________________________________________________
const char *TG4PrimaryVertex::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TG4PrimaryVertex*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TG4PrimaryVertex::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TG4PrimaryVertex*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TG4PrimaryVertex::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TG4PrimaryVertex*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TG4PrimaryVertex::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TG4PrimaryVertex*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TG4PrimaryParticle::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TG4PrimaryParticle::Class_Name()
{
   return "TG4PrimaryParticle";
}

//______________________________________________________________________________
const char *TG4PrimaryParticle::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TG4PrimaryParticle*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TG4PrimaryParticle::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TG4PrimaryParticle*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TG4PrimaryParticle::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TG4PrimaryParticle*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TG4PrimaryParticle::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TG4PrimaryParticle*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TG4Trajectory::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TG4Trajectory::Class_Name()
{
   return "TG4Trajectory";
}

//______________________________________________________________________________
const char *TG4Trajectory::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TG4Trajectory*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TG4Trajectory::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TG4Trajectory*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TG4Trajectory::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TG4Trajectory*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TG4Trajectory::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TG4Trajectory*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TG4TrajectoryPoint::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TG4TrajectoryPoint::Class_Name()
{
   return "TG4TrajectoryPoint";
}

//______________________________________________________________________________
const char *TG4TrajectoryPoint::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TG4TrajectoryPoint*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TG4TrajectoryPoint::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TG4TrajectoryPoint*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TG4TrajectoryPoint::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TG4TrajectoryPoint*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TG4TrajectoryPoint::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TG4TrajectoryPoint*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TG4HitSegment::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TG4HitSegment::Class_Name()
{
   return "TG4HitSegment";
}

//______________________________________________________________________________
const char *TG4HitSegment::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TG4HitSegment*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TG4HitSegment::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TG4HitSegment*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TG4HitSegment::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TG4HitSegment*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TG4HitSegment::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TG4HitSegment*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TG4Event::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TG4Event::Class_Name()
{
   return "TG4Event";
}

//______________________________________________________________________________
const char *TG4Event::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TG4Event*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TG4Event::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TG4Event*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TG4Event::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TG4Event*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TG4Event::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TG4Event*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void TG4PrimaryVertex::Streamer(TBuffer &R__b)
{
   // Stream an object of class TG4PrimaryVertex.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TG4PrimaryVertex::Class(),this);
   } else {
      R__b.WriteClassBuffer(TG4PrimaryVertex::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TG4PrimaryVertex(void *p) {
      return  p ? new(p) ::TG4PrimaryVertex : new ::TG4PrimaryVertex;
   }
   static void *newArray_TG4PrimaryVertex(Long_t nElements, void *p) {
      return p ? new(p) ::TG4PrimaryVertex[nElements] : new ::TG4PrimaryVertex[nElements];
   }
   // Wrapper around operator delete
   static void delete_TG4PrimaryVertex(void *p) {
      delete ((::TG4PrimaryVertex*)p);
   }
   static void deleteArray_TG4PrimaryVertex(void *p) {
      delete [] ((::TG4PrimaryVertex*)p);
   }
   static void destruct_TG4PrimaryVertex(void *p) {
      typedef ::TG4PrimaryVertex current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TG4PrimaryVertex

//______________________________________________________________________________
void TG4PrimaryParticle::Streamer(TBuffer &R__b)
{
   // Stream an object of class TG4PrimaryParticle.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TG4PrimaryParticle::Class(),this);
   } else {
      R__b.WriteClassBuffer(TG4PrimaryParticle::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TG4PrimaryParticle(void *p) {
      return  p ? new(p) ::TG4PrimaryParticle : new ::TG4PrimaryParticle;
   }
   static void *newArray_TG4PrimaryParticle(Long_t nElements, void *p) {
      return p ? new(p) ::TG4PrimaryParticle[nElements] : new ::TG4PrimaryParticle[nElements];
   }
   // Wrapper around operator delete
   static void delete_TG4PrimaryParticle(void *p) {
      delete ((::TG4PrimaryParticle*)p);
   }
   static void deleteArray_TG4PrimaryParticle(void *p) {
      delete [] ((::TG4PrimaryParticle*)p);
   }
   static void destruct_TG4PrimaryParticle(void *p) {
      typedef ::TG4PrimaryParticle current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TG4PrimaryParticle

//______________________________________________________________________________
void TG4Trajectory::Streamer(TBuffer &R__b)
{
   // Stream an object of class TG4Trajectory.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TG4Trajectory::Class(),this);
   } else {
      R__b.WriteClassBuffer(TG4Trajectory::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TG4Trajectory(void *p) {
      return  p ? new(p) ::TG4Trajectory : new ::TG4Trajectory;
   }
   static void *newArray_TG4Trajectory(Long_t nElements, void *p) {
      return p ? new(p) ::TG4Trajectory[nElements] : new ::TG4Trajectory[nElements];
   }
   // Wrapper around operator delete
   static void delete_TG4Trajectory(void *p) {
      delete ((::TG4Trajectory*)p);
   }
   static void deleteArray_TG4Trajectory(void *p) {
      delete [] ((::TG4Trajectory*)p);
   }
   static void destruct_TG4Trajectory(void *p) {
      typedef ::TG4Trajectory current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TG4Trajectory

//______________________________________________________________________________
void TG4TrajectoryPoint::Streamer(TBuffer &R__b)
{
   // Stream an object of class TG4TrajectoryPoint.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TG4TrajectoryPoint::Class(),this);
   } else {
      R__b.WriteClassBuffer(TG4TrajectoryPoint::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TG4TrajectoryPoint(void *p) {
      return  p ? new(p) ::TG4TrajectoryPoint : new ::TG4TrajectoryPoint;
   }
   static void *newArray_TG4TrajectoryPoint(Long_t nElements, void *p) {
      return p ? new(p) ::TG4TrajectoryPoint[nElements] : new ::TG4TrajectoryPoint[nElements];
   }
   // Wrapper around operator delete
   static void delete_TG4TrajectoryPoint(void *p) {
      delete ((::TG4TrajectoryPoint*)p);
   }
   static void deleteArray_TG4TrajectoryPoint(void *p) {
      delete [] ((::TG4TrajectoryPoint*)p);
   }
   static void destruct_TG4TrajectoryPoint(void *p) {
      typedef ::TG4TrajectoryPoint current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TG4TrajectoryPoint

//______________________________________________________________________________
void TG4HitSegment::Streamer(TBuffer &R__b)
{
   // Stream an object of class TG4HitSegment.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TG4HitSegment::Class(),this);
   } else {
      R__b.WriteClassBuffer(TG4HitSegment::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TG4HitSegment(void *p) {
      return  p ? new(p) ::TG4HitSegment : new ::TG4HitSegment;
   }
   static void *newArray_TG4HitSegment(Long_t nElements, void *p) {
      return p ? new(p) ::TG4HitSegment[nElements] : new ::TG4HitSegment[nElements];
   }
   // Wrapper around operator delete
   static void delete_TG4HitSegment(void *p) {
      delete ((::TG4HitSegment*)p);
   }
   static void deleteArray_TG4HitSegment(void *p) {
      delete [] ((::TG4HitSegment*)p);
   }
   static void destruct_TG4HitSegment(void *p) {
      typedef ::TG4HitSegment current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TG4HitSegment

//______________________________________________________________________________
void TG4Event::Streamer(TBuffer &R__b)
{
   // Stream an object of class TG4Event.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TG4Event::Class(),this);
   } else {
      R__b.WriteClassBuffer(TG4Event::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TG4Event(void *p) {
      return  p ? new(p) ::TG4Event : new ::TG4Event;
   }
   static void *newArray_TG4Event(Long_t nElements, void *p) {
      return p ? new(p) ::TG4Event[nElements] : new ::TG4Event[nElements];
   }
   // Wrapper around operator delete
   static void delete_TG4Event(void *p) {
      delete ((::TG4Event*)p);
   }
   static void deleteArray_TG4Event(void *p) {
      delete [] ((::TG4Event*)p);
   }
   static void destruct_TG4Event(void *p) {
      typedef ::TG4Event current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TG4Event

namespace ROOT {
   static TClass *vectorlEintgR_Dictionary();
   static void vectorlEintgR_TClassManip(TClass*);
   static void *new_vectorlEintgR(void *p = 0);
   static void *newArray_vectorlEintgR(Long_t size, void *p);
   static void delete_vectorlEintgR(void *p);
   static void deleteArray_vectorlEintgR(void *p);
   static void destruct_vectorlEintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<int>*)
   {
      vector<int> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<int>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<int>", -2, "vector", 210,
                  typeid(vector<int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEintgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<int>) );
      instance.SetNew(&new_vectorlEintgR);
      instance.SetNewArray(&newArray_vectorlEintgR);
      instance.SetDelete(&delete_vectorlEintgR);
      instance.SetDeleteArray(&deleteArray_vectorlEintgR);
      instance.SetDestructor(&destruct_vectorlEintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<int> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<int>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<int>*)0x0)->GetClass();
      vectorlEintgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEintgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<int> : new vector<int>;
   }
   static void *newArray_vectorlEintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<int>[nElements] : new vector<int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEintgR(void *p) {
      delete ((vector<int>*)p);
   }
   static void deleteArray_vectorlEintgR(void *p) {
      delete [] ((vector<int>*)p);
   }
   static void destruct_vectorlEintgR(void *p) {
      typedef vector<int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<int>

namespace ROOT {
   static TClass *vectorlETG4TrajectoryPointgR_Dictionary();
   static void vectorlETG4TrajectoryPointgR_TClassManip(TClass*);
   static void *new_vectorlETG4TrajectoryPointgR(void *p = 0);
   static void *newArray_vectorlETG4TrajectoryPointgR(Long_t size, void *p);
   static void delete_vectorlETG4TrajectoryPointgR(void *p);
   static void deleteArray_vectorlETG4TrajectoryPointgR(void *p);
   static void destruct_vectorlETG4TrajectoryPointgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TG4TrajectoryPoint>*)
   {
      vector<TG4TrajectoryPoint> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TG4TrajectoryPoint>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TG4TrajectoryPoint>", -2, "vector", 210,
                  typeid(vector<TG4TrajectoryPoint>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETG4TrajectoryPointgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<TG4TrajectoryPoint>) );
      instance.SetNew(&new_vectorlETG4TrajectoryPointgR);
      instance.SetNewArray(&newArray_vectorlETG4TrajectoryPointgR);
      instance.SetDelete(&delete_vectorlETG4TrajectoryPointgR);
      instance.SetDeleteArray(&deleteArray_vectorlETG4TrajectoryPointgR);
      instance.SetDestructor(&destruct_vectorlETG4TrajectoryPointgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TG4TrajectoryPoint> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<TG4TrajectoryPoint>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETG4TrajectoryPointgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<TG4TrajectoryPoint>*)0x0)->GetClass();
      vectorlETG4TrajectoryPointgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETG4TrajectoryPointgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETG4TrajectoryPointgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TG4TrajectoryPoint> : new vector<TG4TrajectoryPoint>;
   }
   static void *newArray_vectorlETG4TrajectoryPointgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TG4TrajectoryPoint>[nElements] : new vector<TG4TrajectoryPoint>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETG4TrajectoryPointgR(void *p) {
      delete ((vector<TG4TrajectoryPoint>*)p);
   }
   static void deleteArray_vectorlETG4TrajectoryPointgR(void *p) {
      delete [] ((vector<TG4TrajectoryPoint>*)p);
   }
   static void destruct_vectorlETG4TrajectoryPointgR(void *p) {
      typedef vector<TG4TrajectoryPoint> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<TG4TrajectoryPoint>

namespace ROOT {
   static TClass *vectorlETG4TrajectorygR_Dictionary();
   static void vectorlETG4TrajectorygR_TClassManip(TClass*);
   static void *new_vectorlETG4TrajectorygR(void *p = 0);
   static void *newArray_vectorlETG4TrajectorygR(Long_t size, void *p);
   static void delete_vectorlETG4TrajectorygR(void *p);
   static void deleteArray_vectorlETG4TrajectorygR(void *p);
   static void destruct_vectorlETG4TrajectorygR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TG4Trajectory>*)
   {
      vector<TG4Trajectory> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TG4Trajectory>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TG4Trajectory>", -2, "vector", 210,
                  typeid(vector<TG4Trajectory>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETG4TrajectorygR_Dictionary, isa_proxy, 4,
                  sizeof(vector<TG4Trajectory>) );
      instance.SetNew(&new_vectorlETG4TrajectorygR);
      instance.SetNewArray(&newArray_vectorlETG4TrajectorygR);
      instance.SetDelete(&delete_vectorlETG4TrajectorygR);
      instance.SetDeleteArray(&deleteArray_vectorlETG4TrajectorygR);
      instance.SetDestructor(&destruct_vectorlETG4TrajectorygR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TG4Trajectory> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<TG4Trajectory>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETG4TrajectorygR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<TG4Trajectory>*)0x0)->GetClass();
      vectorlETG4TrajectorygR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETG4TrajectorygR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETG4TrajectorygR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TG4Trajectory> : new vector<TG4Trajectory>;
   }
   static void *newArray_vectorlETG4TrajectorygR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TG4Trajectory>[nElements] : new vector<TG4Trajectory>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETG4TrajectorygR(void *p) {
      delete ((vector<TG4Trajectory>*)p);
   }
   static void deleteArray_vectorlETG4TrajectorygR(void *p) {
      delete [] ((vector<TG4Trajectory>*)p);
   }
   static void destruct_vectorlETG4TrajectorygR(void *p) {
      typedef vector<TG4Trajectory> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<TG4Trajectory>

namespace ROOT {
   static TClass *vectorlETG4PrimaryVertexgR_Dictionary();
   static void vectorlETG4PrimaryVertexgR_TClassManip(TClass*);
   static void *new_vectorlETG4PrimaryVertexgR(void *p = 0);
   static void *newArray_vectorlETG4PrimaryVertexgR(Long_t size, void *p);
   static void delete_vectorlETG4PrimaryVertexgR(void *p);
   static void deleteArray_vectorlETG4PrimaryVertexgR(void *p);
   static void destruct_vectorlETG4PrimaryVertexgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TG4PrimaryVertex>*)
   {
      vector<TG4PrimaryVertex> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TG4PrimaryVertex>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TG4PrimaryVertex>", -2, "vector", 210,
                  typeid(vector<TG4PrimaryVertex>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETG4PrimaryVertexgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<TG4PrimaryVertex>) );
      instance.SetNew(&new_vectorlETG4PrimaryVertexgR);
      instance.SetNewArray(&newArray_vectorlETG4PrimaryVertexgR);
      instance.SetDelete(&delete_vectorlETG4PrimaryVertexgR);
      instance.SetDeleteArray(&deleteArray_vectorlETG4PrimaryVertexgR);
      instance.SetDestructor(&destruct_vectorlETG4PrimaryVertexgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TG4PrimaryVertex> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<TG4PrimaryVertex>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETG4PrimaryVertexgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<TG4PrimaryVertex>*)0x0)->GetClass();
      vectorlETG4PrimaryVertexgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETG4PrimaryVertexgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETG4PrimaryVertexgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TG4PrimaryVertex> : new vector<TG4PrimaryVertex>;
   }
   static void *newArray_vectorlETG4PrimaryVertexgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TG4PrimaryVertex>[nElements] : new vector<TG4PrimaryVertex>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETG4PrimaryVertexgR(void *p) {
      delete ((vector<TG4PrimaryVertex>*)p);
   }
   static void deleteArray_vectorlETG4PrimaryVertexgR(void *p) {
      delete [] ((vector<TG4PrimaryVertex>*)p);
   }
   static void destruct_vectorlETG4PrimaryVertexgR(void *p) {
      typedef vector<TG4PrimaryVertex> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<TG4PrimaryVertex>

namespace ROOT {
   static TClass *vectorlETG4PrimaryParticlegR_Dictionary();
   static void vectorlETG4PrimaryParticlegR_TClassManip(TClass*);
   static void *new_vectorlETG4PrimaryParticlegR(void *p = 0);
   static void *newArray_vectorlETG4PrimaryParticlegR(Long_t size, void *p);
   static void delete_vectorlETG4PrimaryParticlegR(void *p);
   static void deleteArray_vectorlETG4PrimaryParticlegR(void *p);
   static void destruct_vectorlETG4PrimaryParticlegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TG4PrimaryParticle>*)
   {
      vector<TG4PrimaryParticle> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TG4PrimaryParticle>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TG4PrimaryParticle>", -2, "vector", 210,
                  typeid(vector<TG4PrimaryParticle>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETG4PrimaryParticlegR_Dictionary, isa_proxy, 4,
                  sizeof(vector<TG4PrimaryParticle>) );
      instance.SetNew(&new_vectorlETG4PrimaryParticlegR);
      instance.SetNewArray(&newArray_vectorlETG4PrimaryParticlegR);
      instance.SetDelete(&delete_vectorlETG4PrimaryParticlegR);
      instance.SetDeleteArray(&deleteArray_vectorlETG4PrimaryParticlegR);
      instance.SetDestructor(&destruct_vectorlETG4PrimaryParticlegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TG4PrimaryParticle> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<TG4PrimaryParticle>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETG4PrimaryParticlegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<TG4PrimaryParticle>*)0x0)->GetClass();
      vectorlETG4PrimaryParticlegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETG4PrimaryParticlegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETG4PrimaryParticlegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TG4PrimaryParticle> : new vector<TG4PrimaryParticle>;
   }
   static void *newArray_vectorlETG4PrimaryParticlegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TG4PrimaryParticle>[nElements] : new vector<TG4PrimaryParticle>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETG4PrimaryParticlegR(void *p) {
      delete ((vector<TG4PrimaryParticle>*)p);
   }
   static void deleteArray_vectorlETG4PrimaryParticlegR(void *p) {
      delete [] ((vector<TG4PrimaryParticle>*)p);
   }
   static void destruct_vectorlETG4PrimaryParticlegR(void *p) {
      typedef vector<TG4PrimaryParticle> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<TG4PrimaryParticle>

namespace ROOT {
   static TClass *vectorlETG4HitSegmentgR_Dictionary();
   static void vectorlETG4HitSegmentgR_TClassManip(TClass*);
   static void *new_vectorlETG4HitSegmentgR(void *p = 0);
   static void *newArray_vectorlETG4HitSegmentgR(Long_t size, void *p);
   static void delete_vectorlETG4HitSegmentgR(void *p);
   static void deleteArray_vectorlETG4HitSegmentgR(void *p);
   static void destruct_vectorlETG4HitSegmentgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TG4HitSegment>*)
   {
      vector<TG4HitSegment> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TG4HitSegment>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TG4HitSegment>", -2, "vector", 210,
                  typeid(vector<TG4HitSegment>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETG4HitSegmentgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<TG4HitSegment>) );
      instance.SetNew(&new_vectorlETG4HitSegmentgR);
      instance.SetNewArray(&newArray_vectorlETG4HitSegmentgR);
      instance.SetDelete(&delete_vectorlETG4HitSegmentgR);
      instance.SetDeleteArray(&deleteArray_vectorlETG4HitSegmentgR);
      instance.SetDestructor(&destruct_vectorlETG4HitSegmentgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TG4HitSegment> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<TG4HitSegment>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETG4HitSegmentgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<TG4HitSegment>*)0x0)->GetClass();
      vectorlETG4HitSegmentgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETG4HitSegmentgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETG4HitSegmentgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TG4HitSegment> : new vector<TG4HitSegment>;
   }
   static void *newArray_vectorlETG4HitSegmentgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TG4HitSegment>[nElements] : new vector<TG4HitSegment>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETG4HitSegmentgR(void *p) {
      delete ((vector<TG4HitSegment>*)p);
   }
   static void deleteArray_vectorlETG4HitSegmentgR(void *p) {
      delete [] ((vector<TG4HitSegment>*)p);
   }
   static void destruct_vectorlETG4HitSegmentgR(void *p) {
      typedef vector<TG4HitSegment> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<TG4HitSegment>

namespace ROOT {
   static TClass *maplEstringcOvectorlETG4TrajectorygRsPgR_Dictionary();
   static void maplEstringcOvectorlETG4TrajectorygRsPgR_TClassManip(TClass*);
   static void *new_maplEstringcOvectorlETG4TrajectorygRsPgR(void *p = 0);
   static void *newArray_maplEstringcOvectorlETG4TrajectorygRsPgR(Long_t size, void *p);
   static void delete_maplEstringcOvectorlETG4TrajectorygRsPgR(void *p);
   static void deleteArray_maplEstringcOvectorlETG4TrajectorygRsPgR(void *p);
   static void destruct_maplEstringcOvectorlETG4TrajectorygRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<string,vector<TG4Trajectory> >*)
   {
      map<string,vector<TG4Trajectory> > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<string,vector<TG4Trajectory> >));
      static ::ROOT::TGenericClassInfo 
         instance("map<string,vector<TG4Trajectory> >", -2, "map", 96,
                  typeid(map<string,vector<TG4Trajectory> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEstringcOvectorlETG4TrajectorygRsPgR_Dictionary, isa_proxy, 4,
                  sizeof(map<string,vector<TG4Trajectory> >) );
      instance.SetNew(&new_maplEstringcOvectorlETG4TrajectorygRsPgR);
      instance.SetNewArray(&newArray_maplEstringcOvectorlETG4TrajectorygRsPgR);
      instance.SetDelete(&delete_maplEstringcOvectorlETG4TrajectorygRsPgR);
      instance.SetDeleteArray(&deleteArray_maplEstringcOvectorlETG4TrajectorygRsPgR);
      instance.SetDestructor(&destruct_maplEstringcOvectorlETG4TrajectorygRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<string,vector<TG4Trajectory> > >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<string,vector<TG4Trajectory> >*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEstringcOvectorlETG4TrajectorygRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<string,vector<TG4Trajectory> >*)0x0)->GetClass();
      maplEstringcOvectorlETG4TrajectorygRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEstringcOvectorlETG4TrajectorygRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEstringcOvectorlETG4TrajectorygRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,vector<TG4Trajectory> > : new map<string,vector<TG4Trajectory> >;
   }
   static void *newArray_maplEstringcOvectorlETG4TrajectorygRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,vector<TG4Trajectory> >[nElements] : new map<string,vector<TG4Trajectory> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEstringcOvectorlETG4TrajectorygRsPgR(void *p) {
      delete ((map<string,vector<TG4Trajectory> >*)p);
   }
   static void deleteArray_maplEstringcOvectorlETG4TrajectorygRsPgR(void *p) {
      delete [] ((map<string,vector<TG4Trajectory> >*)p);
   }
   static void destruct_maplEstringcOvectorlETG4TrajectorygRsPgR(void *p) {
      typedef map<string,vector<TG4Trajectory> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<string,vector<TG4Trajectory> >

namespace ROOT {
   static TClass *maplEstringcOvectorlETG4HitSegmentgRsPgR_Dictionary();
   static void maplEstringcOvectorlETG4HitSegmentgRsPgR_TClassManip(TClass*);
   static void *new_maplEstringcOvectorlETG4HitSegmentgRsPgR(void *p = 0);
   static void *newArray_maplEstringcOvectorlETG4HitSegmentgRsPgR(Long_t size, void *p);
   static void delete_maplEstringcOvectorlETG4HitSegmentgRsPgR(void *p);
   static void deleteArray_maplEstringcOvectorlETG4HitSegmentgRsPgR(void *p);
   static void destruct_maplEstringcOvectorlETG4HitSegmentgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<string,vector<TG4HitSegment> >*)
   {
      map<string,vector<TG4HitSegment> > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<string,vector<TG4HitSegment> >));
      static ::ROOT::TGenericClassInfo 
         instance("map<string,vector<TG4HitSegment> >", -2, "map", 96,
                  typeid(map<string,vector<TG4HitSegment> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEstringcOvectorlETG4HitSegmentgRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(map<string,vector<TG4HitSegment> >) );
      instance.SetNew(&new_maplEstringcOvectorlETG4HitSegmentgRsPgR);
      instance.SetNewArray(&newArray_maplEstringcOvectorlETG4HitSegmentgRsPgR);
      instance.SetDelete(&delete_maplEstringcOvectorlETG4HitSegmentgRsPgR);
      instance.SetDeleteArray(&deleteArray_maplEstringcOvectorlETG4HitSegmentgRsPgR);
      instance.SetDestructor(&destruct_maplEstringcOvectorlETG4HitSegmentgRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<string,vector<TG4HitSegment> > >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<string,vector<TG4HitSegment> >*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEstringcOvectorlETG4HitSegmentgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<string,vector<TG4HitSegment> >*)0x0)->GetClass();
      maplEstringcOvectorlETG4HitSegmentgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEstringcOvectorlETG4HitSegmentgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEstringcOvectorlETG4HitSegmentgRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,vector<TG4HitSegment> > : new map<string,vector<TG4HitSegment> >;
   }
   static void *newArray_maplEstringcOvectorlETG4HitSegmentgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,vector<TG4HitSegment> >[nElements] : new map<string,vector<TG4HitSegment> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEstringcOvectorlETG4HitSegmentgRsPgR(void *p) {
      delete ((map<string,vector<TG4HitSegment> >*)p);
   }
   static void deleteArray_maplEstringcOvectorlETG4HitSegmentgRsPgR(void *p) {
      delete [] ((map<string,vector<TG4HitSegment> >*)p);
   }
   static void destruct_maplEstringcOvectorlETG4HitSegmentgRsPgR(void *p) {
      typedef map<string,vector<TG4HitSegment> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<string,vector<TG4HitSegment> >

namespace {
  void TriggerDictionaryInitialization_TG4EventDict_Impl() {
    static const char* headers[] = {
"TG4Event.h",
"TG4PrimaryVertex.h",
"TG4Trajectory.h",
"TG4HitSegment.h",
0
    };
    static const char* includePaths[] = {
"/usr/include/root",
"/afs/cern.ch/user/l/ldinoto/sand-fluka/fluka2edepsim/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "TG4EventDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$TG4PrimaryVertex.h")))  __attribute__((annotate("$clingAutoload$TG4Event.h")))  TG4PrimaryVertex;
namespace std{template <typename _Tp> class __attribute__((annotate("$clingAutoload$bits/allocator.h")))  __attribute__((annotate("$clingAutoload$string")))  allocator;
}
class __attribute__((annotate("$clingAutoload$TG4PrimaryVertex.h")))  __attribute__((annotate("$clingAutoload$TG4Event.h")))  TG4PrimaryParticle;
class __attribute__((annotate("$clingAutoload$TG4Trajectory.h")))  __attribute__((annotate("$clingAutoload$TG4Event.h")))  TG4Trajectory;
class __attribute__((annotate("$clingAutoload$TG4Trajectory.h")))  __attribute__((annotate("$clingAutoload$TG4Event.h")))  TG4TrajectoryPoint;
class __attribute__((annotate("$clingAutoload$TG4HitSegment.h")))  __attribute__((annotate("$clingAutoload$TG4Event.h")))  TG4HitSegment;
namespace std{template <class _CharT> struct __attribute__((annotate("$clingAutoload$bits/char_traits.h")))  __attribute__((annotate("$clingAutoload$string")))  char_traits;
}
class __attribute__((annotate("$clingAutoload$TG4Event.h")))  TG4Event;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "TG4EventDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "TG4Event.h"
#include "TG4PrimaryVertex.h"
#include "TG4Trajectory.h"
#include "TG4HitSegment.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"TG4Event", payloadCode, "@",
"TG4HitSegment", payloadCode, "@",
"TG4PrimaryParticle", payloadCode, "@",
"TG4PrimaryVertex", payloadCode, "@",
"TG4Trajectory", payloadCode, "@",
"TG4TrajectoryPoint", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("TG4EventDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_TG4EventDict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_TG4EventDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_TG4EventDict() {
  TriggerDictionaryInitialization_TG4EventDict_Impl();
}
