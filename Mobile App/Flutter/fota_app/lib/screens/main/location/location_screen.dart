import 'dart:async';

import 'package:flutter/material.dart';
import 'package:fota_app/screens/main/location/location_loading_screen.dart';
import 'package:google_maps_flutter/google_maps_flutter.dart';

import '../../../Service/mqtt_service.dart';
import '../../../constants/mqtt_topics.dart';

/* Location loading screen variable  */
bool g_LocationScreenReady = false;

class LocationScreen extends StatefulWidget {
  static String id = 'Location_Screen';

  const LocationScreen({super.key});

  @override
  State<LocationScreen> createState() => _LocationScreenState();
}

class _LocationScreenState extends State<LocationScreen> {
  late GoogleMapController mapController;
  late Timer timer; // Declare Timer variable
  late bool LiveLocation = false;
  late MQTTService mqttService;
  Marker marker = Marker(
    markerId: const MarkerId('Marker_!'),
    position: const LatLng(30.026452, 31.211458),
    icon: BitmapDescriptor.defaultMarkerWithHue(0),
  );
  double latitude = 30.026452;
  double longitude = 31.211458;

  final Completer<GoogleMapController> _controller =
      Completer<GoogleMapController>();

  static const CameraPosition _kGooglePlex = CameraPosition(
    target: LatLng(30.026452, 31.211458),
    zoom: 17,
  );

  void initializeTimer() {
    timer = Timer.periodic(const Duration(seconds: 1), (Timer t) {
      setState(() {
        // Increment latitude and longitude for demonstration

        // Update marker position
        marker = Marker(
          markerId: const MarkerId('Marker_!'),
          position: LatLng(latitude, longitude),
          icon: BitmapDescriptor.defaultMarkerWithHue(0),
        );
        // Animate camera to new marker position
        mapController
            .animateCamera(CameraUpdate.newLatLng(LatLng(latitude, longitude)));
      });
    });
  }

  void connectToMQTT() {
    mqttService = MQTTService(
        kMQTTtopic, kMQTTclientIdentifier, kMQTTusername, kMQTTpassword);
    mqttService.connect([
      kTopicLocation,
      kMQTTinit,
    ]);

    mqttService.listenForUpdates((String topic, String payload) {
      setState(() {
        /* hena de lw boolean function lazm tt3ml kda  */
        if (topic == kTopicLocation) {
          String locationString =
              payload; // Assuming payload contains "29.979443,31.160891"

          // Split the string by comma
          List<String> locationParts = locationString.split(',');

          // Ensure that the string contains both latitude and longitude
          if (locationParts.length == 2) {
            // Extract latitude and longitude
            latitude = double.tryParse(locationParts[0])!;
            longitude = double.tryParse(locationParts[1])!;
            //print('Location Recevied');

            // Now you can use latitude and longitude as needed
            //  print('Latitude: $latitude, Longitude: $longitude');
          } else {
            // Handle case where payload doesn't contain both latitude and longitude
            //  print('Invalid payload format');
          }
        } else if (topic == kMQTTinit) {
          mqttService.publishMessage(
              kMobileDisconnectTopic, 'Location Screen CONNECTED', kNotRetain);
          /* Topic to initialize the MQTT in the update screen */
          g_LocationScreenReady = true;
        }
      });
    });
  }

  @override
  void initState() {
    super.initState();
    // Start the timer to update location every second
    g_LocationScreenReady = false;
    initializeTimer();
    timer.cancel();

    connectToMQTT();
  }

  @override
  void dispose() {
    super.dispose();
    g_LocationScreenReady = false;
    mapController.dispose();
    timer.cancel(); // Cancel the timer when disposing the widget
    /* refresh the page ready flag */
    mqttService.publishMessage(kMQTTinit, 'true', kRetain);
    mqttService.publishMessage(
        kMobileDisconnectTopic, 'Location Screen DISCONNECTED', kNotRetain);
    mqttService.disconnect();
  }

  @override
  Widget build(BuildContext context) {
    return SafeArea(
      child: Scaffold(
        appBar: AppBar(
          backgroundColor: Colors.black26,
          title: const Text('Location Screen'),
        ),
        body: g_LocationScreenReady
            ? Column(
                children: [
                  Expanded(
                    child: Container(
                      child: GoogleMap(
                        mapType: MapType.normal,
                        initialCameraPosition: _kGooglePlex,
                        onMapCreated: (GoogleMapController controller) {
                          _controller.complete(controller);
                          mapController = controller;
                        },
                        markers: {marker},
                      ),
                    ),
                  ),
                  ElevatedButton(
                    onPressed: () {
                      setState(() {
                        // Update markers set
                        marker = Marker(
                          markerId: const MarkerId('Marker_!'),
                          position: LatLng(latitude, longitude),
                          icon: BitmapDescriptor.defaultMarkerWithHue(0),
                        );
                        // Update camera position with new location and zoom level
                        mapController.animateCamera(
                          CameraUpdate.newLatLngZoom(
                            LatLng(latitude, longitude),
                            17, // Set zoom level to 17
                          ),
                        );
                      });
                    },
                    onLongPress: () {
                      setState(() {
                        LiveLocation = !LiveLocation;
                      });
                      if (LiveLocation == true) {
                        initializeTimer();
                      } else {
                        timer.cancel();
                      }
                    },
                    style: const ButtonStyle(
                      enableFeedback: true,
                      elevation: WidgetStatePropertyAll(10),
                      backgroundColor: WidgetStatePropertyAll(Colors.indigo),
                    ),
                    child: SizedBox(
                      width: 150,
                      child: Row(
                        children: [
                          const Icon(
                            Icons.place,
                            color: Colors.red,
                          ),
                          Text(
                            LiveLocation
                                ? 'Stop Live Location'
                                : 'Show New Location',
                            style: TextStyle(color: Colors.indigo.shade100),
                          ),
                        ],
                      ),
                    ),
                  ),
                ],
              )
            : LocationLoadingScreen(context),
      ),
    );
  }
}
