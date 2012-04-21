/*
 * Name  : ComputationalMoleculeImpl
 * Path  : IComputationalMolecule
 * Use   : Implements stuff common to ComputationalMolecule and
 *         FluxComputationalMolecule classes in order to avoid
 *         code duplication.
 * Author: Sven Schmidt
 * Date  : 04/21/2012
 */
#pragma once

#include "IComputationalMolecule.h"

#include <string>


class ComputationalMoleculeImpl : public IComputationalMolecule {
protected:
    // protected constructor: class should only be used to derive
    //                        from it
    explicit ComputationalMoleculeImpl(std::string const & name);

    std::string const & name() const;

private:
    std::string name_;
};
