/*
 * Name  : ComputationalMeshBuilderTest
 * Path  : 
 * Use   : 
 * Author: Sven Schmidt
 * Date  : 04/21/2012
 */
#pragma once

#include "MeshBuilderMock.h"

#include "FiniteVolume2DLib/BoundaryConditionCollection.h"

#include <cppunit/extensions/HelperMacros.h>


class ComputationalMeshBuilderTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(ComputationalMeshBuilderTest);
    CPPUNIT_TEST(testMeshFileExists);
    CPPUNIT_TEST(buildMeshTest);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

protected:
    void testMeshFileExists();
    void buildMeshTest();

private:
    void initMesh();

private:
    typedef Mesh::Ptr MeshPtr;

private:
    std::string            mesh_filename_;
    static MeshPtr         mesh_;

    /* If we were to use MeshBuilder directly, we would need a default constructor
     * for MeshBuilder, because we need to declare it a static data member.
     * There is no easy way to define a default constructor because of the
     * EntityManager. Hence, this embedded mesh builder.
     */
    static MeshBuilderMock mesh_builder_;

    static BoundaryConditionCollection bc_;
};