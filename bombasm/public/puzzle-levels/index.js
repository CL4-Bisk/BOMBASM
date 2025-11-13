document.querySelector(".to-tutorial-btn").addEventListener("click", e => {
    e.preventDefault();
    window.location.href = "./../tutorial-levels/"
})

const puzzleLevelDisplay = document.querySelector(".levels");
puzzleLevelDisplay.innerHTML = "";    
(async () => {
    const response = await fetch('./../json/puzzle-levels.json'); 
    const puzzles = await response.json();

    puzzles.forEach(level => {
        const locked = (level.locked) ? "disabled": "";
        puzzleLevelDisplay.innerHTML += `
        <button id=${level.number} class="level-btn" ${locked}>${level.number}</button>
        `;    
    })

    puzzleLevelDisplay.querySelectorAll(".level-btn").forEach(level => {
    level.addEventListener("click", () => {
        window.location.href = `./../puzzle/?level=${level.id}`;
        });
    });
})();

