h = 22;


module cuboPrincipal() {
    cube([30, 80, h]);
}

module cuboCanaleta() {
    translate([-8,0,0])
    cube([8, 80, h]);
}

module espacoEsp8266() {
    cube([26,38, h+1]);
}

module espacoFonteAlimentacao() {
    cube([22,31,h+1]);
}

module espacoSeparador() {
    cube([10,38, h+1]);
}

module furoBotaoReset() {
    translate([12.5,-1,1.5+3])
    cube([6, 8, 6]);
}

module furoPassagemFio(offSet) {
    translate([-6,-1+offSet,6])
    cube([6, 8, 6]);
}


module blocoComEspacos() {
    difference() {
        cuboPrincipal();
        // rasgos
        translate([2,1,1.5])
        espacoEsp8266();
        translate([-1,1,6])
        espacoEsp8266();
        translate([4.5,39+5,1.5])
        espacoFonteAlimentacao();
        translate([-1,39+5,6])
        espacoFonteAlimentacao();
        // furos
        furoBotaoReset();
    }
}


module pecaPronta() {
    blocoComEspacos();

    difference() {
        cuboCanaleta();
        translate([-6,1,6])
        espacoEsp8266();
        translate([-6,39+5,6])
        espacoFonteAlimentacao();
        translate([-6,38,6])
        cube([34,5+2, 18]);
        // furos
        furoPassagemFio(0);
        furoPassagemFio(75);
    }
}

module pecaProntaNoLugar() {
    translate([8,0,0])
    pecaPronta();
}

module porca() {
    cylinder(h=2, r=3, $fn=6);
    translate([-6,-2.6,0])
    cube([6,5.2,2]);
}

module furoPorca() {
    cylinder(h=40, r=1.6, $fn=64);
}

module parede() {
    translate([-4,0,0])
    cube([4, 80, h]);
}

module parede2() {
    translate([38,0,0])
    cube([4, 80, h]);
}

module furacao1() {
    translate([-1,4,18])
    porca();
    translate([-1,4,8])
    furoPorca();
}

module furacao2() {
    onde=40-1;
    translate([onde,4,18])
    rotate([0,0,180])
    porca();
    translate([onde,4,8])
    furoPorca();
}

module pecaProntaNoLugarComFuros() {
    translate([4,0,0])
    difference() {
        union() {
            pecaProntaNoLugar();
            parede();
            parede2();
        }
        furacao1();
        translate([0,72,0])
        furacao1();
        furacao2();
        translate([0,72,0])
        furacao2();
    }
}

difference(){
    pecaProntaNoLugarComFuros();
    translate([11,38,22-4])
    cube([6,7,5]);
}
