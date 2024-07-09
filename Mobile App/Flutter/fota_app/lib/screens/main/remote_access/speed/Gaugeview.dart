import 'dart:async';

import 'package:flutter/material.dart';
import 'package:syncfusion_flutter_gauges/gauges.dart';

class Gaugeview extends StatefulWidget {
  final String currentspeed;
  final String maxspeed;
  final bool boolen;

  const Gaugeview({
    required this.currentspeed,
    required this.maxspeed,
    required this.boolen,
    super.key,
  });

  @override
  State<Gaugeview> createState() => _GaugeviewState();
}

class _GaugeviewState extends State<Gaugeview> {
  double _currentValue = 0;
  late Timer _timer;

  @override
  void initState() {
    super.initState();
    _startAnimation();
  }

  @override
  void didUpdateWidget(covariant Gaugeview oldWidget) {
    super.didUpdateWidget(oldWidget);
    // Update the gauge value when the current speed changes
    _updateGaugeValue();
  }

  void _startAnimation() {
    _timer = Timer.periodic(const Duration(milliseconds: 1), (timer) {
      setState(() {
        if (_currentValue < double.parse(widget.currentspeed)) {
          _currentValue += 0.1;
          if (_currentValue >= double.parse(widget.currentspeed) ||
              _currentValue >= double.parse(widget.maxspeed)) {
            // Stop the animation when the gauge value reaches or exceeds the current speed
            _currentValue -= 0.1;
            _timer.cancel();
          }
        } else if (_currentValue > double.parse(widget.currentspeed)) {
          _currentValue -= 0.1;
          if (_currentValue <= double.parse(widget.currentspeed) ||
              _currentValue >= double.parse(widget.maxspeed)) {
            // Stop the animation when the gauge value reaches or exceeds the current speed
            _currentValue += 0.1;
            _timer.cancel();
          }
        }
      });
    });
  }

  void _updateGaugeValue() {
    setState(() {
      // Reset the current value and restart the animation when the current speed changes
      _timer.cancel(); // Cancel the current timer
      _startAnimation(); // Restart animation
    });
  }

  @override
  void dispose() {
    _timer.cancel(); // Cancel the timer when the widget is disposed
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return SizedBox(
      width: 280,
      height: 245,
      // padding: EdgeInsets.all(10),
      child: SfRadialGauge(
        animationDuration: 0,
        axes: [
          RadialAxis(
            minimum: 0,
            maximum: double.parse(widget.maxspeed),
            pointers: [
              NeedlePointer(
                value: _currentValue,
                enableAnimation: widget.boolen,
                needleColor: Colors.white38,
              ),
              RangePointer(
                value: _currentValue,
                width: 20,
                sizeUnit: GaugeSizeUnit.logicalPixel,
                gradient: const SweepGradient(
                  colors: [
                    Color(0xFF00008B),
                    Color(0xFF0000CD),
                    Color(0xFF1E90FF),
                    Color(0xFF00BFFF),
                    Color(0xFF87CEEB),
                    Color(0xFF87CEFA),
                    Color(0xFFB0E0E6),
                    Color(0xFFADD8E6),
                    Color(0xFFAFEEEE),
                    Color(0xFF48D1CC),
                  ],
                ),
              ),
            ],
            annotations: [
              GaugeAnnotation(
                widget: Row(
                  crossAxisAlignment: CrossAxisAlignment.center,
                  mainAxisAlignment: MainAxisAlignment.center,
                  children: [
                    Text(
                      _currentValue.toStringAsFixed(1),
                      style: const TextStyle(color: Colors.white),
                    ),
                    const SizedBox(width: 5),
                    const Text(
                      'km/h',
                      style: TextStyle(color: Colors.white),
                    ),
                  ],
                ),
                angle: 90,
                positionFactor: 0.8,
              ),
            ],
            axisLineStyle: const AxisLineStyle(
              thickness: 15,
            ),
            majorTickStyle: const MajorTickStyle(
              length: 15,
            ),
            minorTickStyle: const MinorTickStyle(
              length: 10,
            ),
            labelOffset: 30,
            interval: double.parse(widget.maxspeed) / 10,
            labelFormat: '{value}',
          ),
        ],
      ),
    );
  }
}
