

#ifndef __resnet18S_H__
#define __resnet18S_H__

#include <vector>
#include <string>
#include <functional>
#include <memory>

#include <opencv2/opencv.hpp>

#include "utils.h"

namespace resnet18
{

/**
 * @brief: Image classification result structure.
 */


/**
 * @brief: Image classification config info.
 */
struct ImageClassificationConfig {
    std::string model_path;
    runtime_t runtime;
    std::vector<std::string> inputLayers;
    std::vector<std::string> outputLayers;
    std::vector<std::string> outputTensors;
};

/**
 * @brief: Custom Pre-Process/Post-Process function objects, not support yet.
 */
typedef std::function<bool(const cv::Mat& frame)> pre_process_t;
typedef std::function<bool(std::vector<float*> &results)> post_process_t;

/**
 * @brief: Image classification instance.
 */
class EXPORT_API ImageClassification {
public:
    /**
     * @brief: Constructor.
     * @Author: tanjatang
     * @param {*}
     * @return {*}
     */
    ImageClassification();

    /**
     * @brief: Deconstructor.
     * @Author: tanjatang
     * @param {*}
     * @return {*}
     */
    ~ImageClassification();

    /**
     * @brief: Init a Image classification instance, must be called before inference.
     * @Author: tanjatang
     * @param {std::string&} model_path: Absolute path of model file.
     * @param {runtime_t} runtime: Inference hardware runtime.
     * @return {bool} true if init successfully, false if failed.
     */    
    bool Init(const ImageClassificationConfig& config);

    /**
     * @brief: Release relevant resources.
     * @Author: tanjatang
     * @param {*}
     * @return {*}
     */
    bool Deinit();

    

    /**
     *  @brief Register pre-process function
     *  @param[in] func   User custom pre-process function.
     *  @retval    true   Register successful.
     *  @retval    false  Register failed.
     */
    bool RegisterPreProcess(pre_process_t func);

    /**
     *  @brief Register post-process function
     *  @param[in] func   User custom post-process function.
     *  @retval    true   Register successful.
     *  @retval    false  Register failed.
     */
    bool RegisterPreProcess(post_process_t func);

    /**
     * @brief: Core method of Image classification.
     * @Author: tanjatang
     * @param {cv::Mat&} image: A RGB format image needs to be detected.
     * @param {std::vector<std::vector<ts::ObjectData> >&} results: Detection results vector for each image.
     * @return {bool} true if detect successfullly, false if failed.
     */
    bool Detect(const cv::Mat& image, std::vector<float*>& results);

    /**
     * @brief: Check Image classification instance initialization state.
     * @Author: tanjatang
     * @return {bool} true if initialized, false if not.
     */
    bool IsInitialized();

private:
    // Image classification handler: all methods of ImageClassification will be forward to it.
    void* impl = nullptr;
};

} // namespace resnet18


#endif // __resnet18S_H__
