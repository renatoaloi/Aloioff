h = 4;

module furoPorca(r) {
    cylinder(h=40, r=r, $fn=64);
}

module furacao1(fh, fp) {
    translate([-1,4,fh])
    furoPorca(fp);
}

module furacao2(fh, fp) {
    onde=40-1;
    translate([onde,4,fh])
    furoPorca(fp);
}

module cuboPrincipal() {
    translate([-4,0,0])
    cube([46, 80, h]);
}

module tampa() {
    translate([4,0,0])
    difference(){
        cuboPrincipal();

        furacao1(-1, 1.6);
        translate([0,72,0])
        furacao1(-1, 1.6);
        furacao2(-1, 1.6);
        translate([0,72,0])
        furacao2(-1, 1.6);
        
        cabeca=3.3;
        furacao1(2, cabeca);
        translate([0,72,0])
        furacao1(2, cabeca);
        furacao2(2, cabeca);
        translate([0,72,0])
        furacao2(2, cabeca);
    }
}

difference(){
    tampa();
    translate([12+2.5,39+2.5,-1])
    cylinder(h=10, r=2, $fn=64);
    translate([12+2.5,39+2.5,2])
    cylinder(h=10, r=4, $fn=64);
    translate([12+2.5,39+2.5,3])
    cylinder(h=10, r=6, $fn=64);
}