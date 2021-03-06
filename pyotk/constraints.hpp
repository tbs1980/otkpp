
#ifndef CONSTRAINTS_HPP

#include <boost/python.hpp>

#include <otkpp/constraints/BoundConstraints.h>
#include <otkpp/lib/Cloneable.h>

using namespace boost::python;

// DEPRECATED
/*struct BoundConstraints_Python : public Cloneable< BoundConstraints_Python, Constraints >
{
  list types;
  list L;
  list U;
  
  BoundConstraints_Python() { }
  
  BoundConstraints_Python(int n)
  {
    for(int i = 0; i < n; i++)
    {
      types.append(BoundConstraints::NONE);
      L.append(0.0);
      U.append(0.0);
    }
  }
  
  operator BoundConstraints() const
  {
    const int n = PyList_Size(types.ptr());
    BoundConstraints BC(n);
    for(int i = 0; i < n; i++)
    {
      BC.types[i] = extract< BoundConstraints::BoundType >(types[i]);
      BC.L[i] = extract< double >(L[i]);
      BC.U[i] = extract< double >(U[i]);
    }
    return BC;
  }
};*/

// DEPRECATED
const Constraints *getOTKConstraintsInstance(const Constraints &C)
{
  /*if(typeid(C) == typeid(BoundConstraints_Python &))
  {
    const BoundConstraints_Python &BC = 
      dynamic_cast< const BoundConstraints_Python & >(C);
    return new BoundConstraints(BC);
  }
  else if(typeid(C) == typeid(NoConstraints &))
    return new NoConstraints();
  else
    throw std::invalid_argument("Unsupported constraints type.");*/
}

void init_constraints()
{
  class_< Constraints, boost::noncopyable >("Constraints", no_init);
  class_< NoConstraints, bases< Constraints > >("NoConstraints");
  class_< BoundConstraints, bases< Constraints > >("BoundConstraints", init< int >())
    .add_property("types", make_getter(&BoundConstraints::types, return_value_policy< return_by_value >()),
                           make_setter(&BoundConstraints::types, return_value_policy< return_by_value >()))
    //.def_readwrite("types", &BoundConstraints::types)
    .add_property("L", make_getter(&BoundConstraints::L, return_value_policy< return_by_value >()),
                       make_setter(&BoundConstraints::L, return_value_policy< return_by_value >()))
    .add_property("U", make_getter(&BoundConstraints::U, return_value_policy< return_by_value >()),
                       make_setter(&BoundConstraints::U, return_value_policy< return_by_value >()));
  enum_< BoundConstraints::BoundType >("BoundType")
    .value("none", BoundConstraints::NONE)
    .value("lower", BoundConstraints::LOWER)
    .value("upper", BoundConstraints::UPPER)
    .value("both", BoundConstraints::BOTH);
  register_ptr_to_python< boost::shared_ptr< Constraints > >();
}

#define CONSTRAINTS_HPP

#endif
