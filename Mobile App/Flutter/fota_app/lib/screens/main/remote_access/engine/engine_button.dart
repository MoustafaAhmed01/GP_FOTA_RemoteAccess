import 'package:flutter/material.dart';

class GradientCircleBorder extends CustomPainter {
  final bool isStarted;

  GradientCircleBorder(this.isStarted);

  @override
  void paint(Canvas canvas, Size size) {
    Paint paint = Paint()
      ..shader = LinearGradient(
        colors: isStarted
            ? [Colors.red.shade100, Colors.red]
            : [Colors.blue.shade50, Colors.blue],
        begin: Alignment.topLeft,
        end: Alignment.bottomRight,
      ).createShader(Rect.fromCircle(
          center: Offset(size.width / 2, size.height / 2),
          radius: size.width / 2))
      ..style = PaintingStyle.stroke
      ..strokeWidth = 5;

    canvas.drawCircle(
        Offset(size.width / 2, size.height / 2), size.width / 2, paint);
  }

  @override
  bool shouldRepaint(covariant CustomPainter oldDelegate) {
    return true;
  }
}
