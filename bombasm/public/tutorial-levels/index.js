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

