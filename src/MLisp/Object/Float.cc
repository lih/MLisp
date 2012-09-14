#include "MLisp/Object/Float.hh"

using namespace MLisp;
using namespace Object;

Ref<INumeric> Float::add(WeakRef<INumeric> _other) const {
  return _other->addF(m_value);
}
Ref<INumeric> Float::sub(WeakRef<INumeric> _other) const {
  return _other->subF(m_value);
}
Ref<INumeric> Float::mul(WeakRef<INumeric> _other) const {
  return _other->mulF(m_value);
}
Ref<INumeric> Float::div(WeakRef<INumeric> _other) const {
  return _other->divF(m_value);
}

Ref<INumeric> Float::addI(int i) const {
  return create(i+m_value);
}
Ref<INumeric> Float::subI(int i) const {
  return create(i-m_value);
}
Ref<INumeric> Float::mulI(int i) const {
  return create(i*m_value);
}
Ref<INumeric> Float::divI(int i) const {
  return create(i/m_value);
}

Ref<INumeric> Float::addF(double f) const {
  return create(f+m_value);
}
Ref<INumeric> Float::subF(double f) const {
  return create(f-m_value);
}
Ref<INumeric> Float::mulF(double f) const {
  return create(f*m_value);
}
Ref<INumeric> Float::divF(double f) const {
  return create(f/m_value);
}

#include <cstdio>
void Float::print() const {
  printf("%lf",m_value);
}
