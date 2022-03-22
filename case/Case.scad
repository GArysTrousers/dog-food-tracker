w = 1;
w45 = w * 0.66; // wall at an angle
body_length = 50;
body_shape = [[0,0],[10,0],[10,5],[5,10],[0,10]];
inside_shape = body_shape + [[w, -w],[-w,-w],[-w,-w45],[-w45,-w],[w,-w]];

switch_radius = 1;
led_radius = 0.5;

// rotate([90])

difference() {
  // Body
  linear_extrude(height=body_length)
  polygon(points=body_shape);

  // Inside Body
  translate([0,0,w]) {
    linear_extrude(height=body_length - w * 2)
    polygon(points=inside_shape);
  }

  translate([5,5,10]) {
    rotate([-90,0,-45]) {
      cylinder(r=switch_radius, h=5, $fn=20);
    }
  }

  translate([4,7,9]) {
    rotate([-90,0,-45]) {
      cylinder(r=led_radius, h=5, $fn=20);
    }
  }
}

