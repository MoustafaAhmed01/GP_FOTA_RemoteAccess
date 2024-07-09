import 'package:flutter/material.dart';

import '../../../../constants/text_style&text_field.dart';

class lock_unlock_icon extends StatelessWidget {
  const lock_unlock_icon({super.key, required this.icon, required this.string});

  final IconData icon;
  final String string;

  @override
  Widget build(BuildContext context) {
    return Container(
      margin: const EdgeInsets.all(10),
      padding: const EdgeInsets.only(
        top: 15,
        bottom: 15,
      ),
      decoration: BoxDecoration(
        color: Colors.black,
        borderRadius: BorderRadius.circular(60),
      ),
      child: Column(children: [
        Icon(
          icon,
          size: 80,
          color: Colors.white,
        ),
        const SizedBox(
          height: 10,
        ),
        Text(
          string,
          style: kTextstyle_white,
        ),
      ]),
    );
  }
}
