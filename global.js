let currentEffect = null;
const confirmSound = new Audio("./audio/buttons/Confirm.wav");
const cancelSound = new Audio("./audio/buttons/Cancel.wav");

confirmSound.volume = 1.0;
cancelSound.volume = 1.0;

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