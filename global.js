let currentEffect = null;
const confirmSound = new Audio("/BOMBASM/audio/buttons/Confirm.wav");
const cancelSound  = new Audio("/BOMBASM/audio/buttons/Cancel.wav");

const explosionSounds = [
    "/BOMBASM/audio/explosions/Explosion 1 - Sound effects Pack 2.wav",
    "/BOMBASM/audio/explosions/Explosion 2 - Sound effects Pack 2.wav",
    "/BOMBASM/audio/explosions/Explosion 3 - Sound effects Pack 2.wav",
    "/BOMBASM/audio/explosions/Explosion 4 - Sound effects Pack 2.wav",
    "/BOMBASM/audio/explosions/Explosion 5 - Sound effects Pack 2.wav",
    "/BOMBASM/audio/explosions/Explosion 6 - Sound effects Pack 2.wav",
    "/BOMBASM/audio/explosions/Explosion 7 - Sound effects Pack 2.wav",
    "/BOMBASM/audio/explosions/Explosion 8 - Sound effects Pack 2.wav",
    "/BOMBASM/audio/explosions/Explosion 9 - Sound effects Pack 2.wav",
    "/BOMBASM/audio/explosions/Explosion 10 - Sound effects Pack 2.wav"
];

const explosionGifs = [
    "/BOMBASM/assets/explosions/1.gif",
    "/BOMBASM/assets/explosions/2.gif",
    "/BOMBASM/assets/explosions/3.gif",
    "/BOMBASM/assets/explosions/4.gif",
    "/BOMBASM/assets/explosions/5.gif",
    "/BOMBASM/assets/explosions/6.gif",
    "/BOMBASM/assets/explosions/7.gif",
    "/BOMBASM/assets/explosions/8.gif",
    "/BOMBASM/assets/explosions/9.gif"
];

confirmSound.volume = 1.0;
cancelSound.volume = 1.0;

export default function addTypeWriterEffect(selector, content, skipby = 1, delayInMS = 50) {
    if (currentEffect) currentEffect.cancel = true;
    
    const effect = { cancel: false };
    currentEffect = effect;

    return new Promise(resolve => {
        let char = 0;
        const dest = document.querySelector(selector);

        function type() {
            if (effect.cancel) return resolve(); 

            dest.textContent = content.slice(0, char) + "_";

            if (char < content.length) {
                char++;
                setTimeout(type, delayInMS);
            } else {
                dest.textContent = content;
                resolve();
            }
        }

        type();
    });
}

export function changeMusic(page, puzzleNumber) {
    document.getElementById("music-frame").contentWindow.postMessage(
        { type: "change-music", page, puzzleNumber },
        "*"
    );
}

export function setupButtonSounds() {
    document.querySelectorAll("button, .main-buttons, .home-btn, .next-btn, .prev-btn, .to-menu-btn, .home-btn, .level-btn").forEach(btn => {
        btn.addEventListener("click", () => {
            confirmSound.currentTime = 0;
            confirmSound.play().catch(()=>{});
        });

        btn.addEventListener("mouseover", () => {
            cancelSound.currentTime = 0;
            cancelSound.play().catch(()=>{});
        });
    });
}

function playRandomExplosion() {
  const randomIndex = Math.floor(Math.random() * explosionSounds.length);
  const audio = new Audio(explosionSounds[randomIndex]);
  audio.volume = 1.0; // optional: adjust volume
  audio.play();
}

function playRandomExplosionGIF() {
    const modal = document.querySelector(".explosion-modal");
    if (!modal){
        return;
    }

    // Create a new img element
    const gif = document.createElement("img");
    gif.src = explosionGifs[Math.floor(Math.random() * explosionGifs.length)];
    gif.style.position = "absolute";
    gif.style.width = `${Math.random() * 850 + 650}px`; // random size between 50-150px
    gif.style.top = `${Math.random() * (modal.clientHeight - 100)}px`;
    gif.style.left = `${Math.random() * (modal.clientWidth - 100)}px`;
    gif.style.pointerEvents = "none"; // allow clicks to pass through
    modal.appendChild(gif);

    setTimeout(() => gif.remove(), 1000);
}

export function startExplosionSequence(duration = 5000) {
  const startTime = Date.now();

  function scheduleNext() {
    playRandomExplosion();
    playRandomExplosionGIF();

    const delay = Math.random() * 400 + 100;

    if (Date.now() - startTime < duration) {
      setTimeout(scheduleNext, delay);
    }
  }

  scheduleNext();
}
