import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:local_auth/local_auth.dart';

import 'alerts.dart';

class FingerprintAuth {
  final LocalAuthentication _auth = LocalAuthentication();

  Future<bool> authenticateWithBiometrics(BuildContext context) async {
    bool canCheckBiometrics = await _auth.canCheckBiometrics;
    if (!canCheckBiometrics) {
      print('Biometric authentication is not available on this device');
      return false;
    }

    try {
      bool authenticated = await _auth.authenticate(
        localizedReason: 'Scan your fingerprint to authenticate',
      );
      return authenticated;
    } catch (e) {
      if (e is PlatformException) {
        errorCheck(context, e.code);
        print('Fingerprint authentication failed with code: ${e.code}');
      } else {
        print('Fingerprint authentication failed: $e');
      }

      return false;
    }
  }
}
