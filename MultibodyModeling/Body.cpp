/* Copyright (c) 2005-6 Stanford University and Michael Sherman.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including 
 * without limitation the rights to use, copy, modify, merge, publish, 
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included 
 * in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**@file
 * Implementations of MassElement Features for Simbody.
 */

#include "SimbodyCommon.h"
#include "Body.h"
#include "BodyRep.h"

#include <string>
#include <iostream> 
#include <sstream>
using std::endl;
using std::ostream;

namespace simtk {

    // BODY //
const RealMeasure& Body::getMassMeasure() const {
    assert(rep);
    return BodyRep::downcast(*rep).getMassMeasure();
}
const StationMeasure& Body::getCentroidMeasure() const {
    assert(rep);
    return BodyRep::downcast(*rep).getCentroidMeasure();
}

Station& Body::addStation(const String& nm) {
    assert(rep);
    return Station::downcast(rep->addFeatureLike(Station(nm), nm));
}
Station& Body::addStation(const String& nm, const StationPlacement& pl) {
    Placement& p = rep->addPlacementLike(pl);
    Station& s = Station::downcast(rep->addFeatureLike(Station(nm), nm));
    s.setPlacement(p);
    return s;
}

Frame& Body::addFrame(const String& nm) {
    assert(rep);
    return Frame::downcast(rep->addFeatureLike(Frame(nm), nm));
}
Frame& Body::addFrame(const String& nm, const FramePlacement& pl) {
    Placement& p = rep->addPlacementLike(pl);
    Frame& s = Frame::downcast(rep->addFeatureLike(Frame(nm), nm));
    s.setPlacement(p);
    return s;
}

const Station& Body::getStation(int i) const {
    assert(rep);
    return Station::downcast(rep->getChildFeature(i));
}
const Station& Body::getStation(const String& nm) const {
    assert(rep);
    const Feature* fp = rep->getChildFeature(nm);
    if (!fp)
        SIMTK_THROW2(Exception::FeatureNameNotFound,"Body::getStation",nm);
    return Station::downcast(*rep->getChildFeature(nm));
}

/*static*/ bool             
Body::isInstanceOf(const Feature& f) {
    if (!FeatureRep::getRep(f)) return false;
    return BodyRep::isA(*FeatureRep::getRep(f));
}
/*static*/ const Body& 
Body::downcast(const Feature& f) {
    assert(isInstanceOf(f));
    return reinterpret_cast<const Body&>(f);
}

/*static*/ Body&       
Body::downcast(Feature& f) {
    assert(isInstanceOf(f));
    return reinterpret_cast<Body&>(f);
}

    // RIGID BODY //

RigidBody::RigidBody(const String& nm) {
    (void)new RigidBodyRep(*this, std::string(nm));
}
RigidBody::RigidBody(const RigidBody& src)
  : Body(src) { }
RigidBody& RigidBody::operator=(const RigidBody& src) {
    Body::operator=(src); return *this;
}
RigidBody::~RigidBody() { }

MassElement& RigidBody::addMassElementLike(const MassElement& me, const String& nm,
                                           const Placement& pl) {
    Placement& p = rep->addPlacementLike(pl);
    MassElement& m = MassElement::downcast(rep->addFeatureLike(me, nm));
    m.setPlacement(p);
    return m;
}
MassElement& RigidBody::addMassElementLike(const MassElement& me, const String& nm) {
    return MassElement::downcast(rep->addFeatureLike(me, nm));
}

/*static*/ bool             
RigidBody::isInstanceOf(const Feature& f) {
    if (!FeatureRep::getRep(f)) return false;
    return RigidBodyRep::isA(*FeatureRep::getRep(f));
}
/*static*/ const RigidBody& 
RigidBody::downcast(const Feature& f) {
    assert(isInstanceOf(f));
    return reinterpret_cast<const RigidBody&>(f);
}

/*static*/ RigidBody&       
RigidBody::downcast(Feature& f) {
    assert(isInstanceOf(f));
    return reinterpret_cast<RigidBody&>(f);
}

    // DEFORMABLE BODY //

    // MULTIBODY //

} // namespace simtk
