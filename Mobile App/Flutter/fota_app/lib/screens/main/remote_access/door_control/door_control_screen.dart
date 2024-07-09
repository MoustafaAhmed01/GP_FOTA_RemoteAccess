import 'package:flutter/material.dart';

import '../../../../Service/mqtt_service.dart';
import '../../../../constants/colours.dart';
import '../../../../constants/mqtt_topics.dart';
import 'lock_unlock.dart';
import 'lock_unlock_icon.dart';

String g_state = ''; //g_previousstate;

class DoorControlScreen extends StatefulWidget {
  static String id = "Screen_DoorControl";

  const DoorControlScreen({super.key});

  @override
  State<DoorControlScreen> createState() => _DoorControlScreenState();
}

class _DoorControlScreenState extends State<DoorControlScreen> {
  late MQTTService mqttService;
  /* MQTT FUNCTION */
  void connectToMQTT() {
    mqttService = MQTTService(
        kMQTTtopic, kMQTTclientIdentifier, kMQTTusername, kMQTTpassword);
    mqttService.connect([
      kMobileDisconnectTopic,
      kLockUnLockTopic,
    ]);

    mqttService.listenForUpdates((String topic, String payload) {
      setState(() {
        String updateState = payload;
        /* hena de lw boolean function lazm tt3ml kda  */
        if (topic == kLockUnLockTopic) {
          g_state = updateState;
          //g_previousstate=updateState;
        }
        /*------------------------------*/
      });
    });
  }

  @override
  void initState() {
    super.initState();

    /* Initialize MQTT */
    connectToMQTT();
  }

  @override
  void dispose() {
    // TODO: implement dispose
    super.dispose();
    // mqttService.disconnect();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text(
          'Door Control',
          style: TextStyle(color: Colors.white),
        ),
      ),
      body: Container(
        decoration: const BoxDecoration(
          image: DecorationImage(
            image: AssetImage('images/door_control.png'), // Path to your image
            fit: BoxFit.cover,
          ),
        ),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.stretch,
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            Row(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                Expanded(
                  child: GestureDetector(
                    onTap: () {
                      setState(() {
                        g_state = 'lock';
                        /*publish message through mqtt*/
                        mqttService.publishMessage(
                            kLockUnLockTopic, g_state, kNotRetain);
                      });
                    },
                    child: lock_unlock(
                      colour:
                          g_state == 'lock' ? kActivecolour : kInactivecolour,
                      child: const lock_unlock_icon(
                          icon: Icons.lock_outlined, string: 'LOCK'),
                    ),
                  ),
                ),
                Expanded(
                  child: GestureDetector(
                    onTap: () {
                      setState(() {
                        g_state = 'unlock';
                        /*publish message through mqtt*/
                        mqttService.publishMessage(
                            kLockUnLockTopic, g_state, kNotRetain);
                      });
                    },
                    child: lock_unlock(
                        colour: g_state == 'unlock'
                            ? kActivecolour
                            : kInactivecolour,
                        child: const lock_unlock_icon(
                            icon: Icons.lock_open_outlined, string: 'UNLOCK')),
                  ),
                ),
              ],
            ),
          ],
        ),
      ),
    );
  }
}
