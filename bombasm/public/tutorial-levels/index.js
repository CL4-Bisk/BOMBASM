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

const tutorialLevelDisplay = document.querySelector(".levels");
tutorialLevelDisplay.innerHTML = "";    
(async () => {
    const response = await fetch('./../json/tutorial-levels.json'); 
    const tutorials = await response.json();

    tutorials.forEach(level => {
        const locked = (level.locked) ? "disabled": "";
        tutorialLevelDisplay.innerHTML += `
        <button id=${level.number} class="level-btn" ${locked}>${level.title}</button>
        `;    
    })

    tutorialLevelDisplay.querySelectorAll(".level-btn").forEach(level => {
    level.addEventListener("click", () => {
        window.location.href = `./../tutorial/?level=${level.id}`;
        });
    });
})();

