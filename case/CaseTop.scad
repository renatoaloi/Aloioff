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