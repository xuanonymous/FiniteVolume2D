/*
 * Name  : EntityMgr
 * Path  : 
 * Use   : Entity manager base class
 * Author: Sven Schmidt
 * Date  : 03/10/2012
 */
#pragma once

#include "EntityCollection.hpp"

#include <map>


template<typename Entity>
class EntityManager {
private:
    typedef typename std::map<IGeometricEntity::Id_t, typename Entity::Ptr> MeshIdMapping_t;

public:
    typedef typename EntityCollection<Entity>::iterator iterator;

public:
    iterator begin() {
        return collection_.begin();
    }

    iterator end() {
        return collection_.end();
    }

    typename Entity::Ptr &
    getEntity(IGeometricEntity::Id_t mesh_id) {
        return mesh_id_mapping_[mesh_id];
    }

protected:
    IGeometricEntity::Id_t getNewEntityIndex() {
        static IGeometricEntity::Id_t index = 0;
        return index++;
    }

    bool findEntity(IGeometricEntity::Id_t mesh_id) const {
        return mesh_id_mapping_.find(mesh_id) != mesh_id_mapping_.end();
    }

protected:
    EntityCollection<Entity> collection_;

    /* The entities are given a unique index in the mesh file so
     * for example faces can reference the vertices they are composed of accurately.
     * This is NOT the unique identifier the vertex is assigned internally
     * however.
     */
    MeshIdMapping_t mesh_id_mapping_;
};
