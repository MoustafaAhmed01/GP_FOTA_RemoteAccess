import 'package:flutter/material.dart';

import '../../../../constants/text_style&text_field.dart';

class title_container extends StatelessWidget {
  const title_container({super.key, required this.text});

  final String text;
  @override
  Widget build(BuildContext context) {
    return Container(
      margin: const EdgeInsets.all(10),
      //padding: EdgeInsets.all(10),
      height: 60,
      decoration: BoxDecoration(
        color: Colors.black87,
        borderRadius: BorderRadius.circular(50),
      ),

      child: Center(
          child: Text(
        text,
        style: kTextstyle2_white,
      )),
    );
  }
}
