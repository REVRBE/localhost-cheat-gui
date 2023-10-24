function update_aimbot(checkbox) {
  var newValue = checkbox.checked ? 'on' : 'off';
  var aimbotOptions = document.querySelector('.aimbot-options');
  if (newValue === 'on') {
    aimbotOptions.style.display = 'block';
  } else {
    aimbotOptions.style.display = 'none';
  }
  var xhr = new XMLHttpRequest();
  xhr.open('GET', '/?aimbot=' + newValue, true);
  xhr.send();
}

function update_silent_aim(checkbox) {
  var newValue = checkbox.checked ? 'on' : 'off';
  var xhr = new XMLHttpRequest();
  xhr.open('GET', '/?silent_aim=' + newValue, true);
  xhr.send();
}

function update_visibility_check(checkbox) {
  var newValue = checkbox.checked ? 'on' : 'off';
  var xhr = new XMLHttpRequest();
  xhr.open('GET', '/?visibility_check=' + newValue, true);
  xhr.send();
}

function update_fov(slider) {
  var newValue = slider.value;
  var xhr = new XMLHttpRequest();
  xhr.open('GET', '/?fov=' + newValue, true);
  xhr.send();
}

function update_smoothness(slider) {
  var newValue = slider.value;
  var xhr = new XMLHttpRequest();
  xhr.open('GET', '/?smoothness=' + newValue, true);
  xhr.send();
}
//AIMBOT END

function update_esp(checkbox) {
  var newValue = checkbox.checked ? 'on' : 'off';
  var espOptions = document.querySelector('.esp-options');
  if (newValue === 'on') {
    espOptions.style.display = 'block';
  } else {
    espOptions.style.display = 'none';
  }
  var xhr = new XMLHttpRequest();
  xhr.open('GET', '/?esp=' + newValue, true);
  xhr.send();
}

function update_checkbox1(checkbox) {
  var newValue = checkbox.checked ? 'on' : 'off';
  var xhr = new XMLHttpRequest();
  xhr.open('GET', '/?checkbox1=' + newValue, true);
  xhr.send();
}

function update_checkbox2(checkbox) {
  var newValue = checkbox.checked ? 'on' : 'off';
  var xhr = new XMLHttpRequest();
  xhr.open('GET', '/?checkbox2=' + newValue, true);
  xhr.send();
}
//ESP END

function update_bunnyhop(checkbox) {
  var newValue = checkbox.checked ? 'on' : 'off';
  var xhr = new XMLHttpRequest();
  xhr.open('GET', '/?bunnyhop=' + newValue, true);
  xhr.send();
}
//BUNNYHOP END