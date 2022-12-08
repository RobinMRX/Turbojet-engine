function init(){
    console.log("> script.js")
    document.getElementById("slider").style.display = 'none'
}


function activ(btn){
    console.log("> script.js > activ()")

    // Changer la couleur du background en vert
    btn.parentElement.parentElement.style.backgroundColor ="#4CAF50"
    
    // Activer le bouton désactiver
    let btnD = btn.parentElement.children[1]
    btnD.classList.remove('disabled')
    btnD.removeAttribute('disabled')

    // Désactiver le bouton activer
    btn.classList.add('disabled')
    btn.setAttribute('disabled', 'disabled')

    // Modifier le texte d'état
    btn.parentElement.parentElement.children[0].children[1].innerHTML = "ON"

    if (btn.parentElement.parentElement.id == "divGaz"){
        btn.parentElement.parentElement.children[2].style.display = 'flex'
        slider.value = 1
        output.innerHTML = slider.value + ' %'

        slider.focus()
    }
}

function desactiv(btn){
    console.log("> script.js > desactiv()")

    // Changer la couleur du background en rouge
    btn.parentElement.parentElement.style.backgroundColor ="#f44336"
    
    // Activer le bouton activer
    let btnA = btn.parentElement.children[0]
    btnA.classList.remove('disabled')
    btnA.removeAttribute('disabled')

    // Désactiver le bouton désactiver
    btn.classList.add('disabled')
    btn.setAttribute('disabled', 'disabled')

    // Modifier le texte d'état
    btn.parentElement.parentElement.children[0].children[1].innerHTML = "OFF"

    if (btn.parentElement.parentElement.id == "divGaz"){
        btn.parentElement.parentElement.children[2].style.display = 'none'
    }
}

let slider = document.getElementById('myRange')
let output = document.getElementById('output')

slider.oninput = function(){
    if (this.value == 0){
        desactiv(this.parentElement.parentElement.children[1].children[1])
        offGaz()
    }
    else{
        output.innerHTML = this.value + ' %'
        sliderGaz(this.value)
    }
}

function onAir(){
    console.log("> script.js > onAir()")
    var xhttp = new XMLHttpRequest()
    xhttp.open("GET", "onAir", true)
    xhttp.send()
}

function offAir(){
    console.log("> script.js > offAir()")
    var xhttp = new XMLHttpRequest()
    xhttp.open("GET", "offAir", true)
    xhttp.send()
}

function onAllu(){
    console.log("> script.js > onAllu()")
    var xhttp = new XMLHttpRequest()
    xhttp.open("GET", "onAllu", true)
    xhttp.send()
}

function offAllu(){
    console.log("> script.js > offAllu()")
    var xhttp = new XMLHttpRequest()
    xhttp.open("GET", "offAllu", true)
    xhttp.send()
}

function onGaz(){
    console.log("> script.js > onGaz()")
    var xhttp = new XMLHttpRequest()
    xhttp.open("GET", "onGaz", true)
    xhttp.send()
}

function offGaz(){
    console.log("> script.js > offGAz()")
    var xhttp = new XMLHttpRequest()
    xhttp.open("GET", "offGaz", true)
    xhttp.send()
}

function sliderGaz(pourcGaz){
    console.log("> script.js > sliderGaz()")
    console.log(pourcGaz)
    var xhttp = new XMLHttpRequest()
    xhttp.open("GET", "/slider?value="+pourcGaz, true)
    xhttp.send()
}

