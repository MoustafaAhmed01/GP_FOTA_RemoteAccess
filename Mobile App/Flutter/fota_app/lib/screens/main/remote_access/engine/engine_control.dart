import 'package:flutter/material.dart';
import 'package:vibration/vibration.dart';

import '../../../../Service/mqtt_service.dart';
import '../../../../constants/mqtt_topics.dart';
import 'engine_button.dart';
import 'engine_loading_screen.dart';

/* Global Variables */
bool g_EngineScreenReady = false;
bool g_EngineState = false;
bool g_EngineFeedback = false; /* Read only Don't change */
late MQTTService mqttService;
/*--------------------------------------------------------*/

class EngineControl_Screen extends StatefulWidget {
  static String id = "Screen_EngineControl";

  const EngineControl_Screen({super.key});

  @override
  State<EngineControl_Screen> createState() => _EngineControl_ScreenState();
}

class _EngineControl_ScreenState extends State<EngineControl_Screen> {
  /* MQTT FUNCTION */
  void connectToMQTT() {
    mqttService = MQTTService(
        kMQTTtopic, kMQTTclientIdentifier, kMQTTusername, kMQTTpassword);
    mqttService.connect([
      kEngineControlTopic,
      kCarEngineFeedbackTopic,
      kMobileDisconnectTopic,
      kMQTTinit,
    ]);
    /* bnbd2 n3ml listen  */
    mqttService.listenForUpdates((String topic, String payload) {
      setState(() {
        bool updateState =
            payload.toLowerCase() == 'true'; // Convert payload to boolean
        /* hena de lw boolean function lazm tt3ml kda  */
        if (topic == kEngineControlTopic) {
          g_EngineState = updateState; /* Send only */
        } else if (topic == kCarEngineFeedbackTopic) {
          g_EngineFeedback = updateState; /* Read only */
        } else if (topic == kMobileDisconnectTopic) {
        } else if (topic == kMQTTinit) {
          mqttService.publishMessage(kMobileDisconnectTopic,
              'Engine Control Screen CONNECTED', kNotRetain);
          /* Topic to initialize the MQTT in the update screen */
          g_EngineScreenReady = true;
        }

        /*------------------------------*/
      });
    });
  }

  @override
  void initState() {
    super.initState();
    g_EngineScreenReady = false;
    /* Initialize MQTT */
    connectToMQTT();
  }

  @override
  void dispose() {
    // TODO: implement dispose
    super.dispose();
    g_EngineScreenReady = false;
    /* refresh the page ready flag */
    mqttService.publishMessage(kMQTTinit, 'true', kRetain);
    mqttService.publishMessage(kMobileDisconnectTopic,
        'Engine Control Screen DISCONNECTED', kNotRetain);
    mqttService.disconnect();
  }

  void _vibrate() {
    Vibration.vibrate(duration: 100); // Vibrate for 100ms
  }

  @override
  Widget build(BuildContext context) {
    return SafeArea(
      child: Scaffold(
        backgroundColor: Colors.black,
        appBar: AppBar(
          backgroundColor: Colors.black,
          title: const Text(
            "Engine Control",
            style: TextStyle(
              color: Colors.white,
              fontWeight: FontWeight.w500,
            ),
          ),
        ),
        body: g_EngineScreenReady
            ? Column(
                mainAxisAlignment: MainAxisAlignment.center,
                children: [
                  Center(
                    child: InkResponse(
                      containedInkWell: true,
                      highlightShape: BoxShape.circle,
                      borderRadius: const BorderRadius.all(Radius.circular(200)),
                      onTap: () {
                        setState(() {
                          g_EngineState = !g_EngineFeedback;
                          mqttService.publishMessage(kEngineControlTopic,
                              g_EngineState.toString(), kNotRetain);
                        });
                        _vibrate();
                      },
                      child: CustomPaint(
                        painter: GradientCircleBorder(g_EngineFeedback),
                        child: Container(
                          width: 200,
                          height: 200,
                          decoration: BoxDecoration(
                            shape: BoxShape.circle,
                            color: Colors.black26,
                            boxShadow: [
                              BoxShadow(
                                color: Colors.black.withOpacity(0.3),
                                spreadRadius: 3,
                                blurRadius: 5,
                                offset: const Offset(0, 3),
                              ),
                            ],
                          ),
                          child: Column(
                            mainAxisAlignment: MainAxisAlignment.center,
                            crossAxisAlignment: CrossAxisAlignment.center,
                            children: [
                              CustomPaint(
                                painter: GradientCircleBorder(g_EngineFeedback),
                                child: Container(
                                  width: 10,
                                  height: 10,
                                  decoration: BoxDecoration(
                                    shape: BoxShape.circle,
                                    color: Colors.black26,
                                    boxShadow: [
                                      BoxShadow(
                                        color: Colors.black.withOpacity(0.3),
                                        spreadRadius: 3,
                                        blurRadius: 50,
                                        offset: const Offset(0, 3),
                                      ),
                                    ],
                                  ),
                                ),
                              ),
                              const SizedBox(
                                height: 10,
                              ),
                              const Center(
                                child: Text(
                                  'Engine',
                                  style: TextStyle(
                                    color: Colors.white,
                                    fontWeight: FontWeight.bold,
                                    fontSize: 35,
                                  ),
                                ),
                              ),
                              Center(
                                child: Text(
                                  g_EngineFeedback ? 'STOP' : 'START',
                                  style: const TextStyle(
                                    color: Colors.white,
                                    fontWeight: FontWeight.bold,
                                    fontSize: 15,
                                  ),
                                ),
                              ),
                            ],
                          ),
                        ),
                      ),
                    ),
                  ),
                ],
              )
            : EngineLoadingScreen(context),
      ),
    );
  }
}
