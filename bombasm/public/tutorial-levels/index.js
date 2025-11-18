document.querySelector(".to-puzzle-btn").addEventListener("click", e => {
    e.preventDefault();
    window.location.href = "./../puzzle-levels/"
})

document.querySelectorAll(".level-btn").forEach(element => {
    element.addEventListener("click", e => {
        e.preventDefault();
        window.location.href = "./../tutorial/"
    });
});


TutorialLevelsModule().then((Module) => {
    const tutorialLevelDisplay = document.querySelector(".levels");
    const getLevelCount = Module.cwrap("getTutorialLevelCount", "number", []);
    const getLevelOperator = Module.cwrap("getTutorialLevelOperator", "string", ["number"]);
    for (let i = 0; i < getLevelCount(); i++) {
        const button = document.createElement("button");
        button.className = "level-btn";
        button.textContent = getLevelOperator(i);
        button.addEventListener("click", () => {
            window.location.href= `./../tutorial/?level=${i}`;
        });
        tutorialLevelDisplay.appendChild(button);
    }
});


