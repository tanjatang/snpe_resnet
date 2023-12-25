

#ifndef __resnet18S_IMPL_H__
#define __resnet18S_IMPL_H__

#include <vector>
#include <string>
#if defined(WIN32) || defined(_WIN32)
#include <time.h>
#else
#include <unistd.h>
#endif
#include <memory>

#include "SNPETask.h"
#include "resnet18.h"

namespace resnet18 {

class ImageClassificationImpl {
public:
    ImageClassificationImpl();
    ~ImageClassificationImpl();
    bool Detect(const cv::Mat& image, std::vector<float*> &results);
    bool Initialize(const ImageClassificationConfig& config);
    bool DeInitialize();

    bool SetScoreThresh(const float& conf_thresh, const float& nms_thresh = 0.5) noexcept {
        this->m_nmsThresh  = nms_thresh;
        this->m_confThresh = conf_thresh;
        return true;
    }

    bool SetROI(const cv::Rect& roi) {
        this->m_roi = roi;
        return true;
    }

    bool RegisterPreProcess(pre_process_t func) {
        this->m_preProcess = func;
        m_isRegisteredPreProcess = true;
        return true;
    }

    bool RegisterPreProcess(post_process_t func) {
        this->m_postProcess = func;
        m_isRegisteredPostProcess = true;
        return true;
    }


    bool IsInitialized() const {
        return m_isInit;
    }

    

private:
    bool m_isInit = false;
    bool m_isRegisteredPreProcess = false;
    bool m_isRegisteredPostProcess = false;

    bool PreProcess(const cv::Mat& frame);
    bool PostProcess(std::vector<float*> &results, int64_t time);

    pre_process_t m_preProcess;
    post_process_t m_postProcess;

    std::unique_ptr<snpetask::SNPETask> m_task;
    std::vector<std::string> m_inputLayers;
    std::vector<std::string> m_outputLayers;
    std::vector<std::string> m_outputTensors;

    int m_labels;
    int m_grids;
    float* m_output;

    cv::Rect m_roi = {0, 0, 0, 0};
    uint32_t m_minBoxBorder = 16;
    float m_nmsThresh = 0.5f;
    float m_confThresh = 0.5f;
    float m_scale;
    int m_xOffset, m_yOffset;
};

} // namespace resnet18

#endif // __resnet18S_IMPL_H__
