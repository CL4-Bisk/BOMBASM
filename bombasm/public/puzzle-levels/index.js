document.querySelector(".to-tutorial-btn").addEventListener("click", e => {
    e.preventDefault();
    window.location.href = "./../tutorial-levels/"
})

PuzzleLevelsModule().then((Module) => {
    const puzzleLevelDisplay = document.querySelector(".levels");
    const getLevelNumber = Module.cwrap("getPuzzleLevelNumber", "number", ["number"]);
    const puzzleCount = Module.cwrap("getPuzzleLevelCount", "number", []);
    for (let i = 0; i < puzzleCount(); i++) {
        const button = document.createElement("button");
        button.id = getLevelNumber(i);
        button.className = "level-btn";
        button.textContent = getLevelNumber(i);
        button.addEventListener("click", () => {
            window.location.href= `./../puzzle/?level=${i}`;
        });
        puzzleLevelDisplay.appendChild(button);
    }
});
