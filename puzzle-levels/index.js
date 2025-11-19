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

    // sessionStorage.setItem("1", "unlocked")
    // sessionStorage.setItem("2", "locked")
    // sessionStorage.setItem("3", "locked")
    // sessionStorage.setItem("4", "locked")
    // sessionStorage.setItem("5", "locked")
    // sessionStorage.setItem("6", "locked")
    // sessionStorage.setItem("7", "locked")

    // if (sessionStorage.getItem("1") === "unlocked") {
    //     document.getElementById("1").disabled = false;
    // }
    // if (sessionStorage.getItem("2") === "unlocked") {
    //     document.getElementById("2").disabled = false;
    // }

    // for testing purposes
    // sessionStorage.setItem("unlockedLevels", "5");

    if (!sessionStorage.getItem("unlockedLevels")) {
        sessionStorage.setItem("unlockedLevels", JSON.stringify([1]));
    }

    const unlockedLevels = JSON.parse(sessionStorage.getItem("unlockedLevels"));
    for (let i = 1; i <= puzzleCount(); i++) {
        if (unlockedLevels.includes(i)) {
            document.getElementById(i).disabled = false;
            console.log("Level " + i + " is unlocked.");
        } else {
            document.getElementById(i).disabled = true;
            console.log("Level " + i + " is locked.");
        }
    }
});
