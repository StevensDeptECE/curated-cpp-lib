/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 4.0.1
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.imebra;

public enum dicomVOIFunction_t {
  linear(imebraJNI.dicomVOIFunction_t_linear_get()),
  linearExact(imebraJNI.dicomVOIFunction_t_linearExact_get()),
  sigmoid(imebraJNI.dicomVOIFunction_t_sigmoid_get());

  public final int swigValue() {
    return swigValue;
  }

  public static dicomVOIFunction_t swigToEnum(int swigValue) {
    dicomVOIFunction_t[] swigValues = dicomVOIFunction_t.class.getEnumConstants();
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (dicomVOIFunction_t swigEnum : swigValues)
      if (swigEnum.swigValue == swigValue)
        return swigEnum;
    throw new IllegalArgumentException("No enum " + dicomVOIFunction_t.class + " with value " + swigValue);
  }

  @SuppressWarnings("unused")
  private dicomVOIFunction_t() {
    this.swigValue = SwigNext.next++;
  }

  @SuppressWarnings("unused")
  private dicomVOIFunction_t(int swigValue) {
    this.swigValue = swigValue;
    SwigNext.next = swigValue+1;
  }

  @SuppressWarnings("unused")
  private dicomVOIFunction_t(dicomVOIFunction_t swigEnum) {
    this.swigValue = swigEnum.swigValue;
    SwigNext.next = this.swigValue+1;
  }

  private final int swigValue;

  private static class SwigNext {
    private static int next = 0;
  }
}
