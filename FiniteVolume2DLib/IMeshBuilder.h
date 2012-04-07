/*
 * Name  : IMeshBuilder
 * Path  : 
 * Use   : Interface for building a mesh
 * Author: Sven Schmidt
 * Date  : 03/03/2012
 */
#pragma once

#include "DeclSpec.h"

#include "IGeometricEntity.h"
#include "Mesh.h"
#include "BoundaryConditionCollection.h"

#include <boost/optional.hpp>
#include <vector>


class DECL_SYMBOLS IMeshBuilder {
public:
    ~IMeshBuilder() {}

    virtual bool buildNode(IGeometricEntity::Id_t vertex_id, bool on_boundary, double x, double y) = 0;
    virtual bool buildFace(IGeometricEntity::Id_t face_id, bool on_boundary, std::vector<IGeometricEntity::Id_t> const & vertex_ids) = 0;
    virtual bool buildCell(IGeometricEntity::Id_t cell_id, std::vector<IGeometricEntity::Id_t> const & face_ids) = 0;
    virtual bool buildBoundaryCondition(IGeometricEntity::Id_t face_id, BoundaryConditionCollection::Type bc_type, double bc_value) = 0;

    virtual boost::optional<Mesh::Ptr> getMesh() const = 0;
};
