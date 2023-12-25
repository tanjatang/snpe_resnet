/*
 * @Description: Implementation of object detection algorithm handler.
 * @version: 2.1
 * @Author: Ricardo Lu<shenglu1202@163.com>
 * @Date: 2022-05-17 20:28:01
 * @LastEditors: Ricardo Lu
 * @LastEditTime: 2023-02-24 15:16:01
 */

#include <math.h>
#include <algorithm>

#include <opencv2/opencv.hpp>

#include "resnet18Impl.h"

namespace resnet18 {

ImageClassificationImpl::ImageClassificationImpl() : m_task(nullptr) {

}

ImageClassificationImpl::~ImageClassificationImpl() {
    DeInitialize();
}

bool ImageClassificationImpl::Initialize(const ImageClassificationConfig& config)
{
    m_task = std::move(std::unique_ptr<snpetask::SNPETask>(new snpetask::SNPETask()));

    m_inputLayers = config.inputLayers;
    m_outputLayers = config.outputLayers;
    m_outputTensors = config.outputTensors;
    m_labels = config.labels;
    m_grids = config.grids;

    m_task->setOutputLayers(m_outputLayers);

    if (!m_task->init(config.model_path, config.runtime)) {
        LOG_ERROR("Can't init snpetask instance.");
        return false;
    }

    m_output = new float[m_grids * m_labels];

    m_isInit = true;
    return true;
}

bool ImageClassificationImpl::DeInitialize()
{
    if (m_task) {
        m_task->deInit();
        m_task.reset(nullptr);
    }

    if (m_output) {
        delete[] m_output;
        m_output = nullptr;
    }

    m_isInit = false;
    return true;
}

bool ImageClassificationImpl::PreProcess(const cv::Mat& image)
{
    auto inputShape = m_task->getInputShape(m_inputLayers[0]);

    size_t batch = inputShape[0];
    size_t inputHeight = inputShape[1];
    size_t inputWidth = inputShape[2];
    size_t channel = inputShape[3];

    if (m_task->getInputTensor(m_inputLayers[0]) == nullptr) {
        LOG_ERROR("Empty input tensor");
        return false;
    }


    cv::Mat input(inputHeight, inputWidth, CV_32FC3, m_task->getInputTensor(m_inputLayers[0]));

    if (image.empty()) {
        LOG_ERROR("Invalid image!");
        return false;
    }

    int imgWidth = image.cols;
    int imgHeight = image.rows;

    m_scale = std::min(inputHeight /(float)imgHeight, inputWidth / (float)imgWidth);
    int scaledWidth = imgWidth * m_scale;
    int scaledHeight = imgHeight * m_scale;
    m_xOffset = (inputWidth - scaledWidth) / 2;
    m_yOffset = (inputHeight - scaledHeight) / 2;

    cv::Mat inputMat(inputHeight, inputWidth, CV_8UC3);


    inputMat.convertTo(input, CV_32FC3);
    input /= 255.0f;
    
    return true;
}

bool ImageClassificationImpl::Detect(const cv::Mat& image,
    std::vector<float*> &results)
{

    // if (m_roi.empty()) {
        
    //     if (m_isRegisteredPreProcess) {
            
    //         m_preProcess(image);} 
    //     else {
    //     PreProcess(image);
    //     LOG_INFO("set the buffer encoding type----------: {}.");
    //     }
    // } else {
        
    //     auto roi_image = image(m_roi);
    //     if (m_isRegisteredPreProcess) m_preProcess(roi_image); 
    //     else PreProcess(roi_image);
        
    // }

    int64_t start = GetTimeStamp_ms();
    if (!m_task->execute()) {
        LOG_ERROR("SNPETask execute failed.");
        return false;
    }
    

    if (m_isRegisteredPostProcess) m_postProcess(results);
    else PostProcess(results, GetTimeStamp_ms() - start);

    return true;
}

bool ImageClassificationImpl::PostProcess(std::vector<float*> &results, int64_t time)
{
    for (size_t i = 0; i < 1; i++) {
        auto outputShape = m_task->getOutputShape(m_outputTensors[i]);
        
        const float* predOutput = m_task->getOutputTensor(m_outputTensors[i]);
        

        float* value1 = new float(predOutput[0]);
        float* value2 = new float(predOutput[1]);

        results.push_back(value1);
        results.push_back(value2);

}


  
    return true;
}

} // namespace resnet18
