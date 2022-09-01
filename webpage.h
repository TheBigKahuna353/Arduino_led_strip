

void printWebPage(String LEDS_on, String cur_func) {
  client.println("<!DOCTYPE html><html>");
  client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  client.println("<link rel=\"icon\" href=\"data:,\">");
  // CSS to style the on/off buttons 
  // Feel free to change the background-color and font-size attributes to fit your preferences
  client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
  client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
  client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
  client.println(".button2 {background-color: #77878A;}</style></head>");
  
  // Web Page Heading
  client.println("<body><h1>ESP8266 Web Server</h1>");
  
  // If the output5State is off, it displays the ON button       
  if (LEDS_on == "on") {
    client.println("<p><a href=\"/off\"><button class=\"button\">ON</button></a></p>");
  } else {
    client.println("<p><a href=\"/on\"><button class=\"button button2\">OFF</button></a></p>");
  } 
  if (cur_func != "func1") {
    client.println("<p><a href=\"/func1\"><button class=\"button\">Rotating Hue</button></a></p>");
  }
  if (cur_func != "func2") {
    client.println("<p><a href=\"/func2\"><button class=\"button\">Simple Red Green</button></a></p>");
  }
  if (cur_func != "func3") {
    client.println("<p><a href=\"/func3\"><button class=\"button\">Simple RGB</button></a></p>");
  }
  if (cur_func != "func4") {
    client.println("<p><a href=\"/func4\"><button class=\"button\">White Fade</button></a></p>");
  }
  if (cur_func != "func5") {
    client.println("<p><a href=\"/func5\"><button class=\"button\">Hue fade</button></a></p>");
  }
  if (cur_func != "on_clap") {
    client.println("<p><a href=\"/on_clap\"><button class=\"button\">On Claps</button></a></p>");
  }

  client.println("<div class=\"color-picker\"></div>");

  client.println("<script>");
 
  client.println("const container = document.querySelector('.color-picker');const canvas = document.createElement('canvas');const circle = document.createElement('div');const txt = document.createElement('div');container.appendChild(canvas);container.appendChild(circle);container.appendChild(txt);container.style.position = 'relative';txt.style.cssText = `font-size: 0.9em; text-align: center;`;circle.style.cssText = `border: 2px solid; border-radius: 50%; width: 12px; height: 12px; position: absolute; top:0; left: 0; pointer-events: none; box-sizing: border-box;`;txt.innerHTML = '&nbsp;';const [width, height] = [container.offsetWidth, container.offsetHeight];[canvas.width, canvas.height] = [width, height];drawColors(canvas);canvas.addEventListener('click', e => pickColor(e, canvas, circle, txt));function pickColor(event, canvas, circle, txt) {const rect = event.target.getBoundingClientRect();const x = event.clientX - rect.left; const y = event.clientY - rect.top;  const context = canvas.getContext('2d');const imgData = context.getImageData(x, y, 1, 1);const [r, g, b] = imgData.data;const [h, s, l] = rgb2hsl(r, g, b);const txtColor = l < 0.5 ? '#FFF' : '#000';circle.style.top = (y - 6) + 'px';circle.style.left = (x - 6) + 'px';circle.style.borderColor = txtColor;txt.innerText = Object.values(toCss(r,g,b,h,s,l)).toString().replace(/\\)\\,/g, ') ');txt.style.backgroundColor = toCss(r,g,b,h,s,l).hex;txt.style.color = txtColor;canvas.dispatchEvent(new CustomEvent('color-selected', {bubbles: true,  detail: {r, g, b, h, s, l} }));");
  client.println("location.href = `http://192.168.1.46/?r${r}g${g}b${b}&`;}");
  client.println("function drawColors(canvas) {const context = canvas.getContext('2d');const {width, height} = canvas;const gradientH = context.createLinearGradient(0, 0, width, 0);gradientH.addColorStop(0, \"rgb(255, 0, 0)\");gradientH.addColorStop(1/6, \"rgb(255, 255, 0)\");gradientH.addColorStop(2/6, \"rgb(0, 255, 0)\");gradientH.addColorStop(3/6, \"rgb(0, 255, 255)\");gradientH.addColorStop(4/6, \"rgb(0, 0, 255)\");gradientH.addColorStop(5/6, \"rgb(255, 0, 255)\");gradientH.addColorStop(1, \"rgb(255, 0, 0)\");context.fillStyle = gradientH;context.fillRect(0, 0, width, height);const gradientV = context.createLinearGradient(0, 0, 0, height);gradientV.addColorStop(0, \"rgba(255, 255, 255, 1)\");gradientV.addColorStop(0.5, \"rgba(255, 255, 255, 0)\");gradientV.addColorStop(0.5, \"rgba(0, 0, 0, 0)\");gradientV.addColorStop(1, \"rgba(0, 0, 0, 1)\");context.fillStyle = gradientV;context.fillRect(0, 0, width, height);}");
  
  client.println("function rgb2hsl(r, g, b) {(r /= 255), (g /= 255), (b /= 255);var max = Math.max(r, g, b), min = Math.min(r, g, b);var h, s, l = (max + min) / 2;if (max == min) {h = s = 0;} else {var d = max - min;s = l > 0.5 ? d / (2 - max - min) : d / (max + min);switch (max) {case r: h = (g - b) / d + (g < b ? 6 : 0); break;case g: h = (b - r) / d + 2; break;case b: h = (r - g) / d + 4; break;}h /= 6;}return [h, s, l];}");
  client.println("function toCss(r, g, b, h, s, l) {const int2hex = num => (Math.round(num) < 16 ? '0' : '') + Math.round(num).toString(16);return {rgb: `rgb(${Math.round(r)},${Math.round(g)},${Math.round(b)})`,hsl: `hsl(${Math.round(360 * h)},${Math.round(100 * s)}%,${Math.round(100 * l)}%)`,hex: `#${int2hex(r)}${int2hex(g)}${int2hex(b)}`};}");
  
  client.println("</script>");
  client.println("</body></html>");
  
  // The HTTP response ends with another blank line
  client.println();
}
