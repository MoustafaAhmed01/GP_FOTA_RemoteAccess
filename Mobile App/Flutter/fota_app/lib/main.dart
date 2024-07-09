import 'package:flutter/material.dart';
import 'package:fota_app/screens/login_screen.dart';
import 'package:fota_app/screens/main/emergency/emergency_screen.dart';
import 'package:fota_app/screens/main/list_tile/Support/support.dart';
import 'package:fota_app/screens/main/list_tile/about_us.dart';
import 'package:fota_app/screens/main/list_tile/settings.dart';
import 'package:fota_app/screens/main/list_tile/team_info.dart';
import 'package:fota_app/screens/main/location/location_screen.dart';
import 'package:fota_app/screens/main/main_screen.dart';
import 'package:fota_app/screens/main/remote_access/ac_control/ac_control_screen.dart';
import 'package:fota_app/screens/main/remote_access/door_control/door_control_screen.dart';
import 'package:fota_app/screens/main/remote_access/engine/engine_control.dart';
import 'package:fota_app/screens/main/remote_access/speed/speed_control_screen.dart';
import 'package:fota_app/screens/main/update/Update_Widgets/update_screen.dart';
import 'package:fota_app/screens/main/update/features/features_screen.dart';
import 'package:fota_app/screens/main/update/firmware_features_screen.dart';
import 'package:fota_app/screens/welcome_screen.dart';

import 'screens/loading_screen.dart';

void main() {
  /* Start the App */
  runApp(const FotaTeamApp());
}

class FotaTeamApp extends StatelessWidget {
  const FotaTeamApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      theme: ThemeData.dark().copyWith(
        textTheme: const TextTheme(
            // bodyLarge: TextStyle(color: Colors.black54),
            ),
      ),
      initialRoute: LoadingScreen.id,
      routes: {
        /*hello motherfucker*/
        LoadingScreen.id: (context) => const LoadingScreen(),
        LoginScreen.id: (context) => const LoginScreen(),
        WelcomeScreen.id: (context) => const WelcomeScreen(),
        MainScreen.id: (context) => const MainScreen(),
        AboutTeam.id: (context) => const AboutTeam(),
        AppSettings.id: (context) => const AppSettings(),
        TeamInfo.id: (context) => const TeamInfo(),
        LocationScreen.id: (context) => const LocationScreen(),
        ScreenUpdate.id: (context) => const ScreenUpdate(),
        EmergencyScreen.id: (context) => const EmergencyScreen(),
        AirCondControlScreen.id: (context) => const AirCondControlScreen(),
        DoorControlScreen.id: (context) => const DoorControlScreen(),
        SpeedControlScreen.id: (context) => const SpeedControlScreen(),
        SupportScreen.id: (context) => const SupportScreen(),
        Firmware_Features_Screen.id: (context) =>
            const Firmware_Features_Screen(),
        Features_Screen.id: (context) => const Features_Screen(),
        EngineControl_Screen.id: (context) => const EngineControl_Screen(),
      },
    );
  }
}
