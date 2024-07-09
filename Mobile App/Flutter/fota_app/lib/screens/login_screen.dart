import 'package:device_info_plus/device_info_plus.dart';
import 'package:firebase_auth/firebase_auth.dart';
import 'package:firebase_database/firebase_database.dart';
import 'package:flutter/material.dart';
import 'package:fota_app/components/fingerprint_service.dart';
import 'package:fota_app/screens/reset_password_screen.dart';
import 'package:intl/intl.dart';
import 'package:local_auth/local_auth.dart';
import 'package:modal_progress_hud_nsn/modal_progress_hud_nsn.dart';

import '../components/alerts.dart';
import '../components/rounded_button.dart';
import '../constants/text_field.dart';
import 'main/main_screen.dart';

class LoginScreen extends StatefulWidget {
  static String id = 'LoginScreen';

  const LoginScreen({super.key});

  @override
  State<LoginScreen> createState() => _LoginScreenState();
}

class _LoginScreenState extends State<LoginScreen> {
  final _auth = FirebaseAuth.instance;
  bool showSpinner = false;
  bool g_LockApp = true;
  bool isCheckedMaster = false;
  String Mobile_Manufacturer_Master = 'samsung';
  String Mobile_HARDWARE_Master = 'exynos2100';
  String g_LockAppPassword = "112233"; // Replace with your desired password
  late String email;
  late String password;
  final FingerprintAuth fingerprintAuth = FingerprintAuth();
  final TextEditingController _emailController = TextEditingController();
  final TextEditingController _passwordController = TextEditingController();
  final DatabaseReference _MobileINFO =
      FirebaseDatabase.instance.ref("CAR_LIST/Elantra/MobileApp");
  final DatabaseReference _MobileLockApp =
      FirebaseDatabase.instance.ref("CAR_LIST/Elantra/MobileApp/LockApp");
  final LocalAuthentication _localAuthentication = LocalAuthentication();

  /* Variable to save the login time*/

  /* Save the login time function */
  void LoginTime() {
    setState(() {
      DateTime currentTime = DateTime.now();
      String formattedTime =
          DateFormat('yyyy-MM-dd hh:mm a').format(currentTime);
      _MobileINFO.update({
        "LastLogin": formattedTime,
      });
    });
  }

  Future<void> GetMobileInfo() async {
    try {
      /* Mobile INFO */
      DeviceInfoPlugin deviceInfo = DeviceInfoPlugin();
      AndroidDeviceInfo androidInfo = await deviceInfo.androidInfo;
      //print(androidInfo);
      _MobileINFO.update({
        "UserINFO":
            'Manufacture: ${androidInfo.manufacturer} ---  Model: ${androidInfo.model} ---  SW Version: ${androidInfo.version}',
      });
      print('Manufacturer: ${androidInfo.manufacturer}');
      print('HARDWARE: ${androidInfo.hardware}');
      if ((androidInfo.hardware == Mobile_HARDWARE_Master) &&
          (androidInfo.manufacturer == Mobile_Manufacturer_Master)) {
        setState(() {
          isCheckedMaster = true;
        });
      } else {
        setState(() {
          isCheckedMaster = false;
        });
      }
    } catch (e) {}
  }

/* Listen */
  void ListenFun() {
    /* Current states */
    _MobileLockApp.onValue.listen((DatabaseEvent event) {
      final dataCurrent = event.snapshot.value;
      if (event.snapshot.exists &&
          dataCurrent != null &&
          dataCurrent is Map<Object?, Object?>) {
        // Update the state with the new software version
        setState(() {
          g_LockApp = dataCurrent['State'] as bool;
          g_LockAppPassword = dataCurrent['Password'] as String;
        });
      } else {
        print('Data type: ${dataCurrent.runtimeType}');
      }
    });
  }

  void showPasswordDialog() {
    String input = "";
    showDialog<String>(
      context: context,
      builder: (BuildContext context) {
        return AlertDialog(
          scrollable: true,
          title: const Text('Enter Password'),
          content: TextField(
            keyboardType: TextInputType.number,
            obscureText: true,
            onChanged: (value) {
              setState(() {
                input = value;
              });
            },
          ),
          actions: <Widget>[
            Row(
              mainAxisAlignment: MainAxisAlignment.end,
              children: [
                Column(
                  children: [
                    TextButton(
                      child: const Text('Reset'),
                      onPressed: () {
                        Navigator.of(context).pop();
                        Navigator.push(
                          context,
                          MaterialPageRoute(
                              builder: (context) => ResetPasswordScreen(
                                  isMaster: isCheckedMaster)),
                        );
                      },
                    ),
                  ],
                ),
                TextButton(
                  child: const Text('Cancel'),
                  onPressed: () {
                    Navigator.of(context).pop();
                  },
                ),
                TextButton(
                  child: const Text('OK'),
                  onPressed: () {
                    Navigator.of(context).pop(input);
                    if (input == g_LockAppPassword) {
                      if (isCheckedMaster) {
                        setState(() {
                          g_LockApp = !g_LockApp;
                          _MobileLockApp.update(
                            {
                              "State": g_LockApp,
                            },
                          );
                        });
                        ScaffoldMessenger.of(context).showSnackBar(
                          SnackBar(
                            content: Text(
                              g_LockApp
                                  ? 'Locked: Your vehicle is secured'
                                  : 'Unlocked: Anyone can access your vehicle',
                              style: const TextStyle(
                                color: Colors.white,
                              ),
                            ),
                            backgroundColor: Colors.white12,
                          ),
                        );
                      } else {
                        ScaffoldMessenger.of(context).showSnackBar(
                          const SnackBar(
                            content: Text(
                              'Only the owner can lock/unlock the access',
                              style: TextStyle(
                                color: Colors.white,
                              ),
                            ),
                            backgroundColor: Colors.white12,
                          ),
                        );
                      }
                    } else {
                      ScaffoldMessenger.of(context).showSnackBar(
                        const SnackBar(
                          content: Text(
                            'Password is incorrect',
                            style: TextStyle(
                              color: Colors.white,
                            ),
                          ),
                          backgroundColor: Colors.white12,
                        ),
                      );
                    }
                  },
                ),
              ],
            ),
          ],
        );
      },
    );
  }

  @override
  void initState() {
    // TODO: implement initState
    super.initState();
    ListenFun();
    GetMobileInfo();
  }

  /* Get mobile INFO */
  @override
  void dispose() {
    // Clean up the TextEditingController when the widget is disposed
    _emailController.dispose();
    _passwordController.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return SafeArea(
      child: Scaffold(
        backgroundColor: Colors.transparent,
        body: ModalProgressHUD(
          inAsyncCall: showSpinner,
          child: Stack(
            fit: StackFit.expand,
            children: [
              Image.asset(
                'images/Mercedes_front.png',
                fit: BoxFit.cover,
              ),
              Column(
                children: [
                  Padding(
                    padding: const EdgeInsets.only(left: 20, top: 20),
                    child: Row(
                      children: [
                        Flexible(
                          child: Hero(
                            tag: 'logo',
                            child: SizedBox(
                              height: 20,
                              child: Image.asset('images/FOTA_Logo.png'),
                            ),
                          ),
                        ),
                        const SizedBox(
                          width: 20,
                        ),
                        const Text(
                          'FOTA Team',
                          style: TextStyle(
                            fontSize: 20,
                            fontWeight: FontWeight.bold,
                          ),
                        ),
                      ],
                    ),
                  ),
                  true
                      ? Expanded(
                          flex: 1,
                          child: SingleChildScrollView(
                            child: Column(
                              children: [
                                Padding(
                                  padding: const EdgeInsets.only(
                                    left: 270,
                                  ),
                                  child: GestureDetector(
                                    onTap: showPasswordDialog,
                                    child: Container(
                                      width: 70,
                                      height: 80,
                                      decoration: const BoxDecoration(
                                        color: Colors.black26,
                                        borderRadius: BorderRadius.all(
                                            Radius.circular(30)),
                                      ),
                                      child: Column(
                                        mainAxisAlignment:
                                            MainAxisAlignment.center,
                                        children: [
                                          g_LockApp
                                              ? const Icon(
                                                  Icons.lock_person_sharp)
                                              : const Icon(
                                                  Icons.lock_open_rounded),
                                          const Text(
                                            'Master Control',
                                            textAlign: TextAlign.center,
                                          ),
                                        ],
                                      ),
                                    ),
                                  ),
                                ),
                              ],
                            ),
                          ),
                        )
                      : Expanded(
                          flex: 1,
                          child: Container(),
                        ),
                  Expanded(
                    flex: 1,
                    child: SingleChildScrollView(
                      child: Container(
                        child: Column(
                          mainAxisAlignment: MainAxisAlignment.end,
                          children: [
                            TextField(
                              keyboardType: TextInputType.emailAddress,
                              controller: _emailController,
                              textAlign: TextAlign.center,
                              style: const TextStyle(
                                color: Colors.white,
                              ),
                              onChanged: (value) {
                                //Do something with the user input.
                                email = value;
                              },
                              decoration: kTextFieldDecoration.copyWith(
                                  hintText: 'Enter your email'),
                            ),
                            const SizedBox(
                              height: 26.0,
                            ),
                            TextField(
                              obscureText: true,
                              controller: _passwordController,
                              textAlign: TextAlign.center,
                              style: const TextStyle(
                                color: Colors.white,
                              ),
                              onChanged: (value) {
                                //Do something with the user input.
                                password = value;
                              },
                              decoration: kTextFieldDecoration.copyWith(
                                  hintText: 'Enter your password'),
                            ),
                            const SizedBox(
                              height: 26.0,
                            ),
                            RoundedButton(
                                title: 'Log In',
                                color: Colors.lightBlueAccent,
                                onPressed: () async {
                                  setState(() {
                                    showSpinner = true;
                                  });
                                  try {
                                    final user =
                                        await _auth.signInWithEmailAndPassword(
                                            email: email, password: password);
                                    /* Clear el email wi password 2bl mtmshy */
                                    _emailController.clear();
                                    _passwordController.clear();
                                    /* Reset the varibles 3shan mytl3sh w ydkhol y3ml login tany */
                                    email = '';
                                    password = '';
                                    if (g_LockApp) {
                                      if (isCheckedMaster) {
                                        /* update the login time */
                                        LoginTime();

                                        toastFun('Signed In!');
                                        Navigator.pushNamed(
                                            context, MainScreen.id);

                                        setState(() {
                                          showSpinner = false;
                                        });
                                      } else {
                                        setState(() {
                                          showSpinner = false;
                                        });
                                        // App is locked and this device is not the master
                                        toastFun('App is Locked by the Owner');
                                        setState(() {
                                          showSpinner = false;
                                        });
                                      }
                                    } else {
                                      /* update the login time */
                                      LoginTime();

                                      toastFun('Signed In!');
                                      Navigator.pushNamed(
                                          context, MainScreen.id);

                                      setState(() {
                                        showSpinner = false;
                                      });
                                    }
                                  } catch (e) {
                                    setState(() {
                                      showSpinner = false;
                                    });
                                    if (e is FirebaseAuthException) {
                                      errorCheck(context, e.code);
                                      print(e.code);
                                      // Handle the error here based on e.code or e.message
                                    } else {
                                      errorCheck(context, ' ');
                                      setState(() {
                                        showSpinner = false;
                                      });
                                    }
                                  }
                                },
                                labelSize: 14),
                            RoundedButton(
                              title: 'Fingerprint',
                              color: Colors.lightBlueAccent,
                              onPressed: () async {
                                bool isAuthenticated = await fingerprintAuth
                                    .authenticateWithBiometrics(context);
                                if (isAuthenticated) {
                                  if (g_LockApp) {
                                    if (isCheckedMaster) {
                                      // Do something when authentication is successful and the app is not locked
                                      try {
                                        setState(() {
                                          showSpinner = true;
                                        });
                                        final user = await _auth
                                            .signInWithEmailAndPassword(
                                                email: 'fotateam@gmail.com',
                                                password: '123456');

                                        _emailController.clear();
                                        _passwordController.clear();
                                        /* Reset the varibles 3shan mytl3sh w ydkhol y3ml login tany */
                                        email = '';
                                        password = '';
                                        /* update the login time */
                                        LoginTime();
                                        toastFun('Signed In');
                                        Navigator.pushNamed(
                                            context, MainScreen.id);
                                        setState(() {
                                          showSpinner = false;
                                        });
                                      } catch (e) {
                                        setState(() {
                                          showSpinner = false;
                                        });
                                        if (e is FirebaseAuthException) {
                                          errorCheck(context, e.code);
                                          print(e.code);
                                          // Handle the error here based on e.code or e.message
                                        } else {
                                          errorCheck(context, ' ');
                                          setState(() {
                                            showSpinner = false;
                                          });
                                        }
                                      }
                                      setState(() {
                                        showSpinner = false;
                                      });
                                    } else {
                                      setState(() {
                                        showSpinner = false;
                                      });
                                      // App is locked and this device is not the master
                                      toastFun('App is Locked by the Owner');
                                      setState(() {
                                        showSpinner = false;
                                      });
                                    }
                                  } else {
                                    // Do something when authentication is successful and the app is not locked
                                    try {
                                      setState(() {
                                        showSpinner = true;
                                      });
                                      final user = await _auth
                                          .signInWithEmailAndPassword(
                                              email: 'fotateam@gmail.com',
                                              password: '123456');

                                      _emailController.clear();
                                      _passwordController.clear();
                                      /* Reset the varibles 3shan mytl3sh w ydkhol y3ml login tany */
                                      email = '';
                                      password = '';
                                      /* update the login time */
                                      LoginTime();
                                      toastFun('Signed In');
                                      Navigator.pushNamed(
                                          context, MainScreen.id);
                                      setState(() {
                                        showSpinner = false;
                                      });
                                    } catch (e) {
                                      setState(() {
                                        showSpinner = false;
                                      });
                                      if (e is FirebaseAuthException) {
                                        errorCheck(context, e.code);
                                        print(e.code);
                                        // Handle the error here based on e.code or e.message
                                      } else {
                                        errorCheck(context, ' ');
                                        setState(() {
                                          showSpinner = false;
                                        });
                                      }
                                    }
                                    setState(() {
                                      showSpinner = false;
                                    });
                                  }
                                  print('Authentication successful');
                                } else {
                                  setState(() {
                                    showSpinner = false;
                                  });
                                  // Do something when authentication fails
                                  print('Authentication failed');
                                  toastFun('Fingerprint Declined');
                                  setState(() {
                                    showSpinner = false;
                                  });
                                }
                              },
                              labelSize: 14,
                            ),
                          ],
                        ),
                      ),
                    ),
                  ),
                ],
              ),
            ],
          ),
        ),
      ),
    );
  }
}
