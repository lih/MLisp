#include "MLisp/Object/Integer.hh"
#include "MLisp/Object/Float.hh"

using namespace MLisp;
using namespace Object;

Ref<INumeric> Integer::add(WeakRef<INumeric> _other) const {
  return _other->addI(m_value);
}
Ref<INumeric> Integer::sub(WeakRef<INumeric> _other) const {
  return _other->subI(m_value);
}
Ref<INumeric> Integer::mul(WeakRef<INumeric> _other) const {
  return _other->mulI(m_value);
}
Ref<INumeric> Integer::div(WeakRef<INumeric> _other) const {
  return _other->divI(m_value);
}

Ref<INumeric> Integer::addI(int i) const {
  return create(i+m_value);
}
Ref<INumeric> Integer::subI(int i) const {
  return create(i-m_value);
}
Ref<INumeric> Integer::mulI(int i) const {
  return create(i*m_value);
}
Ref<INumeric> Integer::divI(int i) const {
  return create(i/m_value);
}

Ref<INumeric> Integer::addF(double f) const {
  return Float::create(f+m_value);
}
Ref<INumeric> Integer::subF(double f) const {
  return Float::create(f-m_value);
}
Ref<INumeric> Integer::mulF(double f) const {
  return Float::create(f*m_value);
}
Ref<INumeric> Integer::divF(double f) const {
  return Float::create(f/m_value);
}

#include <cstdio>
void Integer::print() const {
  printf("%d",m_value);
}
bool Integer::equal(const IObject& _other) const {
  if(_other.is<Integer>())
    return static_cast<const Integer&>(_other).m_value==m_value;
  else
    return false;
}
