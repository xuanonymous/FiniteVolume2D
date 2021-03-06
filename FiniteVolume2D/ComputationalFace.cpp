#include "ComputationalFace.h"

#include "FluxComputationalMolecule.h"

#include "FiniteVolume2DLib/Util.h"

#include <boost/format.hpp>

#include <exception>
#include <cassert>


ComputationalFace::ComputationalFace(Face::Ptr const & geometric_face, EntityCollection<ComputationalNode> const & cnodes)
    :
    geometric_face_(geometric_face), cnodes_(cnodes) , bc_(nullptr) {
    assert(cnodes_.size() == 2);
}

IGeometricEntity::Id_t
ComputationalFace::id() const {
    return geometric_face_->id();
}

IGeometricEntity::Id_t
ComputationalFace::meshId() const {
    // computational faces have no mesh id
    return IGeometricEntity::undef();
}

IGeometricEntity::Entity_t
ComputationalFace::getEntityType() const {
    return geometric_face_->getEntityType();
}

EntityCollection<Node> const &
ComputationalFace::getNodes() const {
    return geometric_face_->getNodes();
}

double
ComputationalFace::area() const {
    return geometric_face_->area();
}

Vector
ComputationalFace::normal() const {
    return geometric_face_->normal();
}

Vertex
ComputationalFace::centroid() const {
    return geometric_face_->centroid();
}

EntityCollection<ComputationalNode> const &
ComputationalFace::getComputationalNodes() const {
    return cnodes_;
}

ComputationalNode const &
ComputationalFace::startNode() const {
    return *(cnodes_[0]);
}

ComputationalNode const &
ComputationalFace::endNode() const {
    return *(cnodes_[1]);
}

Face::Ptr const &
ComputationalFace::geometricEntity() const {
    return geometric_face_;
}

BoundaryCondition::Ptr const &
ComputationalFace::getBoundaryCondition() const {
    return bc_;
}

void
ComputationalFace::setBoundaryCondition(BoundaryCondition::Ptr const & bc) {
    bc_ = bc;
}

FluxComputationalMolecule &
ComputationalFace::getComputationalMolecule(std::string const & name) {
    auto it = cm_.find(name);
    if (it == cm_.end()) {
        boost::format format = boost::format("ComputationalFace::getComputationalMolecule: No computational molecule found for \
                                                variable %1% and face %2%!\n") % name % meshId();
        Util::error(format.str());

        // have to throw because we only return by reference
        throw std::exception(format.str().c_str());
    }
    return it->second;
}

void
ComputationalFace::addComputationalMolecule(std::string const & name) {
    cm_[name] = FluxComputationalMolecule(name);
}

void
ComputationalFace::addUserDefValue(std::string const & id, boost::any const & value) {
    user_def_var_[id] = value;
}

boost::any const &
ComputationalFace::getUserDefValue(std::string const & id) {
    auto it = user_def_var_.find(id);
    if (it == user_def_var_.end()) {
        boost::format format = boost::format("ComputationalFace::getUserDefValue: No user-defined variable with name %1% found \
                                             in computational face %2%!\n") % id % meshId();
        Util::error(format.str());

        // have to throw because we only return by reference
        throw std::exception(format.str().c_str());
    }
    return it->second;
}
