/**
 *  @file  morphology.hpp
 *  @brief header for morphology.hpp that implements functions for mathematical
 *         image processing, in particular dilation and erosion basis
 */

#include <opencv2/opencv.hpp>

/**
 * @brief  compute a morphological dilation or erosion on a grayscale image
 *         with a given structuring element. Dilation or erosion
 *         processing depends on an order function  defined by the pointer pf
 * @param  se: the structing element shape umber
 * @param  ims: the input image source to process
 * @param  imd: the destination image
 * @param  pf: a pointer on a ordering function
 */
void
mm(cv::Mat se, cv::Mat ims, cv::Mat imd, void (*pf)(uchar, uchar*));


/**
 * @brief  ordering function, if val is geater than max then update max
 * @param  val: the input value
 * @param  max: the value to update
 */
void
maximum(uchar val, uchar* max);

/**
 * @brief  ordering function, if val is geater than max then update max
 * @param  val: the input value
 * @param  max: the value to update
 */
void
minimum(uchar val, uchar* min);
