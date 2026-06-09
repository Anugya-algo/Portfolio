document.addEventListener("scroll", function () {
    const parallaxElements = document.querySelectorAll(".parallax");
    const scrollTop = window.pageYOffset;

    parallaxElements.forEach(el => {
        const speed = parseFloat(el.getAttribute("data-speed"));
        el.style.transform = `translateY(${scrollTop * speed}px)`;
    });
});
