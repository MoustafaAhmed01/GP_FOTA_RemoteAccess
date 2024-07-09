import 'dart:async';

import 'package:firebase_database/firebase_database.dart';
import 'package:flutter/material.dart';
import 'package:fluttertoast/fluttertoast.dart';
import 'package:fota_app/screens/main/update/Update_Widgets/PendingInstallation_widget.dart';

import '../../../../Service/mqtt_service.dart';
import '../../../../components/alerts.dart';
import '../../../../constants/mqtt_topics.dart';
import 'noupdate_widget.dart';
import 'updatefound_widget.dart';
import 'updatescreen_loading.dart';

/* Current Data */
String g_CurrentSoftwareVersion = '';
String g_CurrentSoftwareDate = '';
bool g_CurrentUpdateState = false;
/* New Data */
String g_SoftwareDescription = '';
String g_FileName = '';
String g_NewSoftwareVersion = '';
String g_SoftwareDate = '';
bool g_UpdateFound = false;
bool g_DownloadComplete = false;
bool g_FileDownloaded = false;
bool g_FileInstalled = false;
bool g_ConfirmUpdate = false;
bool g_InstallStart = false;
bool g_InstallationDone = false;
bool g_InstallationFailure = false;
bool g_ESPStartedDownload = false;
String g_ESPDownloadPercentage = '0';
String g_ESPInstallPercentage = '0';
/* Loading Screen Variables */
bool g_ScreenReady = false;
late MQTTService mqttService;

/*------------------------------------------------------------------------*/
class ScreenUpdate extends StatefulWidget {
  static String id = 'Screen_Update';

  const ScreenUpdate({super.key});

  @override
  State<ScreenUpdate> createState() => _ScreenUpdateState();
}

class _ScreenUpdateState extends State<ScreenUpdate> {
  /* Database Reference */
  final DatabaseReference _databaseReference =
      FirebaseDatabase.instance.ref('CAR_LIST/Elantra/MobileApp/NewFirmware');
  final DatabaseReference _CurrentMobileInfo =
      FirebaseDatabase.instance.ref("CAR_LIST/Elantra/MobileApp");
  final DatabaseReference _CurrentCarInfo =
      FirebaseDatabase.instance.ref("CAR_LIST/Elantra/OTA");
  /* MQTT Service */

  /*-----------------------------------------------------*/

  /* Variable to include the software version */
  Future<void> _handleRefresh() async {
    // Simulate a delay before refreshing
    await Future.delayed(const Duration(seconds: 1));
    setState(() {
      // Toggle the value of updateFound
      g_CurrentUpdateState = g_UpdateFound;

      /* Update the Current State on the cloud*/
      _CurrentMobileInfo.update({
        "CurrentState": g_CurrentUpdateState,
      });
    });
  }

  /* If the app was completely close and then tried to open again, it should open
  * on the same widget that you had before closing the app */
  Future<void> _FirstScreen() async {
    // Simulate a delay before refreshing
    final ref = FirebaseDatabase.instance
        .ref('CAR_LIST/Elantra/MobileApp/CurrentState');
    final snapshot = await ref.child('').get();
    bool updateState = false; // default value
    if (snapshot.exists) {
      updateState = snapshot.value as bool;
    } else {
      print('No data available.');
    }
    setState(() {
      g_CurrentUpdateState = updateState;
    });
  }

  /* Listen */
  void ListenFun() {
    /* Current states */
    _CurrentMobileInfo.onValue.listen((DatabaseEvent event) {
      final dataCurrent = event.snapshot.value;
      if (event.snapshot.exists &&
          dataCurrent != null &&
          dataCurrent is Map<Object?, Object?>) {
        // Update the state with the new software version
        setState(() {
          g_CurrentSoftwareDate = dataCurrent['CurrentDate'] as String;
          g_CurrentSoftwareVersion = dataCurrent['CurrentVersion'] as String;
          g_CurrentUpdateState = dataCurrent['CurrentState'] as bool;
        });
      } else {
        print('Data type: ${dataCurrent.runtimeType}');
      }
    });

    /* New states */
    _databaseReference.onValue.listen((DatabaseEvent event) {
      final data = event.snapshot.value;
      if (event.snapshot.exists &&
          data != null &&
          data is Map<Object?, Object?>) {
        // Update the state with the new software version
        setState(() {
          g_SoftwareDate = data['UploadedOn'] as String;
          g_FileName = data['Filename'] as String;
          g_NewSoftwareVersion = data['New_Firmware_version'] as String;
          g_SoftwareDescription = data['Description'] as String;
          g_FileDownloaded = data['Downloaded'] as bool;
          g_FileInstalled = data['Installed'] as bool;
        });
      } else {
        print('Data type: ${data.runtimeType}');
      }
    });
  }

  /* Button Pressed for confirmation */
  void ButtonPressed() {
    setState(() {
      g_ConfirmUpdate ? g_ConfirmUpdate = false : g_ConfirmUpdate = true;
      mqttService.publishMessage(
          kConfirmUpdateTopic, g_ConfirmUpdate.toString(), kRetain);
    });
  }

  /* After downloading how to behave ? */
  void DownloadConfirmed() {
    setState(() async {
      /* hena 23mly cancel  l 2y toast mn 2bl kda w ro7ly 3la loading screen mn tany  */
      Fluttertoast.cancel();
      toastFun('Download Complete');
      g_ScreenReady = false;

      await _CurrentMobileInfo.update({
        "CurrentState": false,
      });
      /* de 3la l MQTT */
      /* hena bnrg3 l Confirm 3la l update l false tany  */
      g_ConfirmUpdate = false;
      mqttService.publishMessage(
          kConfirmUpdateTopic, g_ConfirmUpdate.toString(), kRetain);
      await _databaseReference.update({
        'Downloaded': true,
      });
/* hena bnrg3 tany el downloadconfirmation to false 2no not confirmed y3ny  */
      /* hena bnrg3 tany el downloadconfirmation to false 2no not confirmed y3ny  */
      mqttService.publishMessage(kDownloadConfirmationTopic, 'false', kRetain);
      //mqttService.publishMessage(kDownloadConfirmationTopic, 'false', kRetain);
      /* hena bnrg3 tany l NewUpdate l false 2n mfysh update y3ny */
      mqttService.publishMessage(kNewUpdateTopic, 'false', kRetain);
      /* refresh the page ready flag */
      mqttService.publishMessage(kMQTTinit, 'true', kRetain);
      /* nrg3 l Download Start tany  */
      mqttService.publishMessage(kUpdateDownloadStart, 'false', kRetain);
      /* nrg3 l percentage to 0 */
      mqttService.publishMessage(kDownloadPercentage, '0', kRetain);
      /* hena bn5ly l current page t3ml refresh tany  */
      _FirstScreen();
      _handleRefresh();
    });
  }

/* After downloading how to behave ? */
  void InstallationConfirmed() {
    setState(() async {
      /* hena 23mly cancel  l 2y toast mn 2bl kda w ro7ly 3la loading screen mn tany  */
      Fluttertoast.cancel();
      toastFun('Installation Complete');
      g_ScreenReady = false;

      /* de 3la l MQTT */
      /* hnrg3 l confirmation bta3 l install  */
      g_InstallationDone = false;
      mqttService.publishMessage(
          kInstallationDone, g_InstallationDone.toString(), kRetain);
      g_InstallStart = false;
      mqttService.publishMessage(
          kStartIntalling, g_InstallStart.toString(), kRetain);
      g_InstallationFailure = false;
      mqttService.publishMessage(
          kInstallationFailure, g_InstallationFailure.toString(), kRetain);
      /* Reset the percentage  again */
      mqttService.publishMessage(kInstallPercentage, '0', kRetain);
      /* refresh the page ready flag */
      mqttService.publishMessage(kMQTTinit, 'true', kRetain);
      /* hena bn3ml save ll values bt3t l current values */
      await _CurrentMobileInfo.update({
        "CurrentState": false,
        'CurrentDate': g_SoftwareDate,
        'CurrentVersion': g_NewSoftwareVersion,
      });
      await _CurrentCarInfo.update({
        "Vehicle_State": 'Up to Date',
      });
      await _databaseReference.update({
        'Installed': true,
      });
      Fluttertoast.cancel();
      toastFun('Successfully Installed');
      /* hena bn5ly l current page t3ml refresh tany  */
      _FirstScreen();
      _handleRefresh();
    });
  }

  void InstallationFailure() {
    setState(() {
      g_ScreenReady = false;

      /* de 3la l MQTT */
      /* hena bnrg3 l Confirm 3la l update l false tany  */
      g_ConfirmUpdate = false;
      mqttService.publishMessage(
          kConfirmUpdateTopic, g_ConfirmUpdate.toString(), kRetain);

      /* hena bnrg3 tany el downloadconfirmation to false 2no not confirmed y3ny  */
      mqttService.publishMessage(kDownloadConfirmationTopic, 'false', kRetain);
      //mqttService.publishMessage(kDownloadConfirmationTopic, 'false', kRetain);
      /* hena bnrg3 tany l NewUpdate l false 2n mfysh update y3ny */
      mqttService.publishMessage(kNewUpdateTopic, 'true', kRetain);

      /* nrg3 l Download Start tany  */
      mqttService.publishMessage(kUpdateDownloadStart, 'false', kRetain);
      /* nrg3 l percentage to 0 */
      mqttService.publishMessage(kDownloadPercentage, '0', kRetain);
      /* hnrg3 l confirmation bta3 l install  */
      g_InstallationDone = false;
      mqttService.publishMessage(
          kInstallationDone, g_InstallationDone.toString(), kRetain);
      g_InstallStart = false;
      mqttService.publishMessage(
          kStartIntalling, g_InstallStart.toString(), kRetain);
      g_InstallationFailure = false;
      mqttService.publishMessage(
          kInstallationFailure, g_InstallationFailure.toString(), kRetain);
      /* Reset the percentage  again */
      mqttService.publishMessage(kInstallPercentage, '0', kRetain);

      _CurrentMobileInfo.update({
        "CurrentState": true,
      });
      _databaseReference.update({
        'Downloaded': false,
      });
      _CurrentCarInfo.update({
        "Vehicle_State": 'Pending',
      });
      _databaseReference.update({
        'Installed': false,
      });
      /* refresh the page ready flag */
      _FirstScreen();
      mqttService.publishMessage(kMQTTinit, 'true', kRetain);
      _handleRefresh();
    });
  }

  /* MQTT FUNCTION */
  void connectToMQTT() {
    mqttService = MQTTService(
        kMQTTtopic, kMQTTclientIdentifier, kMQTTusername, kMQTTpassword);
    mqttService.connect([
      kMobileDisconnectTopic,
      kNewUpdateTopic,
      kDownloadConfirmationTopic,
      kConfirmUpdateTopic,
      kUpdateDownloadStart,
      kDownloadPercentage,
      kInstallPercentage,
      kInstallationFailure,
      kStartIntalling,
      kInstallationDone,
      kMQTTinit,
    ]);
    /* 3shan lw mfysh retain message f lazm yb3t message l 2wl t2dr t3mlo init w ysht8l */
    // mqttService.publishMessage(kMQTTinit, 'true', kRetain);
    /* bnbd2 n3ml listen  */
    mqttService.listenForUpdates((String topic, String payload) {
      setState(() {
        bool updateState =
            payload.toLowerCase() == 'true'; // Convert payload to boolean
        /* hena de lw boolean function lazm tt3ml kda  */
        if (topic == kNewUpdateTopic) {
          g_UpdateFound = updateState;
          if (g_UpdateFound == true) {
            _CurrentCarInfo.update({
              "Vehicle_State": 'Pending',
            });
          } else {
            g_CurrentUpdateState = false;
            _CurrentMobileInfo.update({
              "CurrentState": false,
            });
            _CurrentCarInfo.update({
              "Vehicle_State": 'Up to Date',
            });
          }
        } else if (topic == kDownloadConfirmationTopic) {
          g_DownloadComplete = updateState;
        } else if (topic == kConfirmUpdateTopic) {
          g_ConfirmUpdate = updateState;
        } else if (topic == kMobileDisconnectTopic) {
        } else if (topic == kDownloadPercentage) {
          g_ESPDownloadPercentage = payload;
        } else if (topic == kInstallPercentage) {
          g_ESPInstallPercentage = payload;
        } else if (topic == kUpdateDownloadStart) {
          g_ESPStartedDownload = updateState;
        } else if (topic == kInstallationDone) {
          g_InstallationDone = updateState;
        } else if (topic == kInstallationFailure) {
          g_InstallationFailure = updateState;

          if (g_InstallationFailure == true) {
            Fluttertoast.cancel();
            toastFun('Installing Failure!');
            InstallationFailure();
          } else {
            /* Do nothing */
          }
        } else if (topic == kStartIntalling) {
          g_InstallStart = updateState;
        } else if (topic == kMQTTinit) {
          mqttService.publishMessage(
              kMobileDisconnectTopic, 'Update Screen CONNECTED', kNotRetain);
          /* Topic to initialize the MQTT in the update screen */
          g_ScreenReady = true;
        }
        /* If update was found  */
        if (g_DownloadComplete == true) {
          if (g_ConfirmUpdate == true) {
            DownloadConfirmed();
          } else {}
        } else {}

        /* Installation Done */
        if (g_InstallationDone == true) {
          InstallationConfirmed();
        } else {}
        /*------------------------------*/
      });
    });
  }

  @override
  void initState() {
    super.initState();

    /* Go to loading screen first */
    g_ScreenReady = false;
    /* Initialize MQTT */
    connectToMQTT();
    /* Update the first screen */
    _FirstScreen();

    // Listen for changes in the database
    ListenFun();
  }

  @override
  void dispose() {
    // TODO: implement dispose
    super.dispose();
    g_ScreenReady = false;
    /* refresh the page ready flag */
    mqttService.publishMessage(kMQTTinit, 'true', kRetain);
    mqttService.publishMessage(
        kMobileDisconnectTopic, 'Update Screen DISCONNECTED', kNotRetain);
    mqttService.disconnect();
  }

  @override
  Widget build(BuildContext context) {
    return SafeArea(
      child: Scaffold(
        backgroundColor: Colors.black,
        appBar: AppBar(
          backgroundColor: Colors.black,
          title: const Text(
            "Firmware Update",
            style: TextStyle(
              color: Colors.white,
              fontWeight: FontWeight.w500,
            ),
          ),
        ),
        body: Container(
          padding: const EdgeInsets.all(25),
          child: RefreshIndicator(
            backgroundColor: Colors.white54,
            color: Colors.black87,
            edgeOffset: 20,
            onRefresh: _handleRefresh,
            child: ListView(
              children: <Widget>[
                g_ScreenReady
                    ? (g_CurrentUpdateState
                        ? UpdateFoundContainer(ButtonPressed)
                        : (g_FileInstalled || !g_FileDownloaded)
                            ? NoUpdateContainer()
                            : PendingInstallationContainer())
                    : UpdateLoadingScreen(context),
              ],
            ),
          ),
        ),
      ),
    );
  }
}
