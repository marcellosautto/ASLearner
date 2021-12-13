import cv2
import os
import numpy as np
import tensorflow as tf
from object_detection.utils import label_map_util
from object_detection.utils import visualization_utils as viz_utils
from object_detection.builders import model_builder
from object_detection.utils import config_util
from object_detection.protos import pipeline_pb2
from google.protobuf import text_format

#file paths
WORKSPACE_PATH = 'Tensorflow/workspace'
SCRIPTS_PATH = 'Tensorflow/scripts'
APIMODEL_PATH = 'Tensorflow/models'
ANNOTATION_PATH = WORKSPACE_PATH + '/annotations'
IMAGE_PATH = WORKSPACE_PATH + '/images'
MODEL_PATH = WORKSPACE_PATH + '/models'
PRETRAINED_MODEL_PATH = WORKSPACE_PATH + '/pre-trained-models'
CONFIG_PATH = MODEL_PATH + '/my_ssd_mobnet/pipeline.config'
CHECKPOINT_PATH = MODEL_PATH + '/my_ssd_mobnet/'
CUSTOM_MODEL_NAME = 'my_ssd_mobnet'

#path for MLM configuration file
CONFIG_PATH = MODEL_PATH + '/' + CUSTOM_MODEL_NAME + '/pipeline.config'
config = config_util.get_configs_from_pipeline_file(CONFIG_PATH)

# Load pipeline config and build a detection model
configs = config_util.get_configs_from_pipeline_file(CONFIG_PATH)
detection_model = model_builder.build(model_config=configs['model'], is_training=False)

# Restore checkpoint
ckpt = tf.compat.v2.train.Checkpoint(model=detection_model)
ckpt.restore(os.path.join(CHECKPOINT_PATH, 'ckpt-62')).expect_partial()


category_index = label_map_util.create_category_index_from_labelmap(ANNOTATION_PATH + '/label_map.pbtxt')
# Setup capture
#cap = cv2.VideoCapture(0)
#width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
#height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))

@tf.function
def detect_fn(image):
    image, shapes = detection_model.preprocess(image)
    prediction_dict = detection_model.predict(image, shapes)
    detections = detection_model.postprocess(prediction_dict, shapes)
    return detections

def set_detections(image_np):
        
        #image_np = np.array(image_np)
        #detect input with tensorflow object detection api
        input_tensor = tf.convert_to_tensor(np.expand_dims(image_np, 0), dtype=tf.float32)
        detections = detect_fn(input_tensor)
    
        #store detectionsq
        num_detections = int(detections.pop('num_detections'))
        detections = {key: value[0, :num_detections].numpy()
                      for key, value in detections.items()}
        detections['num_detections'] = num_detections

        # detection_classes should be ints.
        detections['detection_classes'] = detections['detection_classes'].astype(np.int64)

        return detections


def get_detection_char(image_np):

    detections = set_detections(image_np)
    return detections['detection_classes'][0]


def get_detection_frame(image_np):

        detections = set_detections(image_np)
        return detections['detection_classes'][0]
        label_id_offset = 1
        #image_np_with_detections = image_np.copy()

        #display detections on screen with accuracy
        viz_utils.visualize_boxes_and_labels_on_image_array(image_np,
                    detections['detection_boxes'],
                    detections['detection_classes'] + label_id_offset,
                    detections['detection_scores'],
                    category_index,
                    use_normalized_coordinates=True,
                    max_boxes_to_draw=5,
                    min_score_thresh=.5,
                    agnostic_mode=False)

        #display camera I/O
        #cv2.imshow('object detection', cv2.resize(image_np_with_detections,
        #(800, 600)))
    
        #Press 'q' to quit
        #if cv2.waitKey(1) & 0xFF == ord('q'):

        return image_np
            #cap.release()
            #break

        #detect inputs
        detections = detect_fn(input_tensor)
        #from matplotlib import pyplot as plt


#def main():

#   while cap.isOpened():
#       ret, frame = cap.read()

#       frame = cv2.flip(frame, 1)
#       image_np = np.array(frame)
#       detections = set_detections(image_np)

#       #Press 'q' to quit
#       if cv2.waitKey(1) & 0xFF == ord('q'):
#           cap.release()
#           break

#       #Press 'e' to enter answer
#       if cv2.waitKey(1) & 0xFF == ord('e'):
#           #print(get_detection_char(detections))
#           return get_detection_char(detections)

#    #display camera I/O
#       cv2.imshow('object detection', cv2.resize(get_detection_frame(detections, image_np),
#        (800, 600)))

#main()