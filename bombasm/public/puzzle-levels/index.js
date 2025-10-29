document.querySelector(".to-tutorial-btn").addEventListener("click", e => {
    e.preventDefault();
    window.location.href = "./../tutorial-levels/"
})


document.querySelectorAll(".level-btn").forEach(element => {
    element.addEventListener("click", e => {
        e.preventDefault();
        window.location.href = "./../puzzle/"
    });
});
