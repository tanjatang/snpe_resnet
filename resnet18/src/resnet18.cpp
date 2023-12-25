/*
 * @Description: Implementation of Face Detection algorithm APIs.
 * @version: 2.1
 * @Author: Ricardo Lu<shenglu1202@163.com>
 * @Date: 2022-05-17 20:26:56
 * @LastEditors: Ricardo Lu
 * @LastEditTime: 2022-07-12 08:24:29
 */

#if defined(WIN32) || defined(_WIN32)
#include <time.h>
#else
#include <unistd.h>
#endif

#include "resnet18Impl.h"

namespace resnet18 {

ImageClassification::ImageClassification()
{
    impl = new ImageClassificationImpl();
}

ImageClassification::~ImageClassification()
{
    if (nullptr != impl) {
        delete static_cast<ImageClassificationImpl*>(impl);
        impl = nullptr;
    }
}

bool ImageClassification::Init(const ImageClassificationConfig& config)
{
    if (IsInitialized()) {
        return static_cast<ImageClassificationImpl*>(impl)->DeInitialize() &&
               static_cast<ImageClassificationImpl*>(impl)->Initialize(config);
    } else {
        return static_cast<ImageClassificationImpl*>(impl)->Initialize(config);
    }
}

bool ImageClassification::Deinit()
{
    if (nullptr != impl && IsInitialized()) {
        return static_cast<ImageClassificationImpl*>(impl)->DeInitialize();
    } else {
        LOG_ERROR("ImageClassification: deinit failed!");
        return false;
    }
}

bool ImageClassification::IsInitialized()
{
    return static_cast<ImageClassificationImpl*>(impl)->IsInitialized();
}

bool ImageClassification::Detect(const cv::Mat& image, std::vector<float*> &results)
{
    
    if (nullptr != impl && IsInitialized()) {
        
        auto ret = static_cast<ImageClassificationImpl*>(impl)->Detect(image, results);
        
        return ret;
    } else {
        LOG_ERROR("ImageClassification::Detect failed caused by incompleted initialization!");
        return false;
    }
}

bool ImageClassification::SetScoreThreshold(const float& conf_thresh, const float& nms_thresh)
{
    if (nullptr != impl) {
        return static_cast<ImageClassificationImpl*>(impl)->SetScoreThresh(conf_thresh, nms_thresh);
    } else {
        LOG_ERROR("ImageClassification::SetScoreThreshold failed because incompleted initialization!");
        return false;
    }
}

bool ImageClassification::SetROI(const cv::Rect& roi)
{
    if (nullptr != impl) {
        return static_cast<ImageClassificationImpl*>(impl)->SetROI(roi);
    } else {
        LOG_ERROR("ImageClassification::SetROI failed because incompleted initialization!");
        return false;
    }
}

bool ImageClassification::RegisterPreProcess(pre_process_t func)
{
    if (nullptr != impl) {
        return static_cast<ImageClassificationImpl*>(impl)->RegisterPreProcess(func);
    } else {
        LOG_ERROR("ImageClassification::RegisterPreProcess failed because incompleted initialization!");
        return false;
    }
}

bool ImageClassification::RegisterPreProcess(post_process_t func)
{
    if (nullptr != impl) {
        return static_cast<ImageClassificationImpl*>(impl)->RegisterPreProcess(func);
    } else {
        LOG_ERROR("ImageClassification::RegisterPreProcess failed because incompleted initialization!");
        return false;
    }
}

} // namespace resnet18
