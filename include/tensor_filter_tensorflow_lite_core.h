/**
 * Copyright (C) 2018 Samsung Electronics Co., Ltd. All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 */
/**
 * @file   tensor_filter_tensorflow_lite_core.h
 * @author HyoungJoo Ahn <hello.ahn@samsung.com>
 * @date   7/5/2018
 * @brief	 connection with tflite libraries.
 *
 * @bug     No known bugs.
 */
#ifndef TENSOR_FILTER_TENSORFLOW_LITE_H
#define TENSOR_FILTER_TENSORFLOW_LITE_H

#ifdef __cplusplus
#include <iostream>
#include <stdint.h>
#include <glib.h>

#include <tensorflow/contrib/lite/model.h>
#include <tensorflow/contrib/lite/optional_debug_tools.h>
#include <tensorflow/contrib/lite/string_util.h>
#include <tensorflow/contrib/lite/kernels/register.h>

#include "tensor_typedef.h"

/**
 * @brief	ring cache structure
 */
class TFLiteCore
{
public:
  /**
   * member functions.
   */
  TFLiteCore (const char *_model_path);
   ~TFLiteCore ();

  /**
   * @brief	get the model path.
   * @return	saved model path.
   */
  const char *getModelPath ()
  {
    return model_path;
  }
  int loadModel ();
  const char *getInputTensorName ();
  const char *getOutputTensorName ();

  double get_ms(struct timeval t);
  int getInputTensorSize ();
  int getOutputTensorSize ();
  int getInputTensorDim (int idx, tensor_dim dim, tensor_type * type);
  int getOutputTensorDim (int idx, tensor_dim dim, tensor_type * type);
  int getInputTensorDimSize ();
  int getOutputTensorDimSize ();
  int invoke (uint8_t * inptr, uint8_t ** outptr);

private:
  /**
   * member variables.
   */
  const char *model_path;
  std::unique_ptr < tflite::Interpreter > interpreter;
  std::unique_ptr < tflite::FlatBufferModel > model;
  int getTensorType(int tensor_idx, tensor_type *type);
  int getTensorDim (int tensor_idx, tensor_dim dim, tensor_type * type);
};

/**
 * @brief	the definition of functions to be used at C files.
 */
extern "C"
{
#endif

  extern void *tflite_core_new (const char *_model_path);
  extern void tflite_core_delete (void *tflite);
  extern const char *tflite_core_getModelPath (void *tflite);
  extern int tflite_core_getInputDim (void *tflite, int idx, tensor_dim dim,
      tensor_type * type);
  extern int tflite_core_getOutputDim (void *tflite, int idx, tensor_dim dim,
      tensor_type * type);
  extern int tflite_core_getInputSize (void *tflite);
  extern int tflite_core_getOutputSize (void *tflite);
  extern int tflite_core_invoke (void *tflite, uint8_t * inptr,
      uint8_t ** outptr);

#ifdef __cplusplus
}
#endif

#endif
