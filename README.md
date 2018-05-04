# Ray Tracing In A Weekend
based the book &lt;Ray Tracing in a weekend>, I should finish it in the Winter hollday, but I was too lazy to finish it.

Sorry for my teacher and senior [@Danielhu229](https://github.com/Danielhu229) and thanks to your guide!

### theory
Maybe this picture explain the relationship of camera(or eyes) and the pixel .
![](https://wx4.sinaimg.cn/mw690/0071GCRRly1fquryr4se4j30yf0e23yy.jpg)

### Chapter 1
We use C++ to output a text ppm file,and use some software to preview it. Such as [xnViewMP](https://www.xnview.com/en/xnviewmp/).
More about PPM:[PPM](https://zh.wikipedia.org/wiki/PBM%E6%A0%BC%E5%BC%8F#PPM%E4%BE%8B%E5%AD%90)

### Chapter 2
If we want to simulate point and ray as it in real world, we can build vec3 class to abstract it.
And we can add some necessary operators and functions.

### Chapter 3
> At the core of a ray tracer is to send rays through pixels and compute what color is seen in the direction of those rays. This is of the form calculate which ray goes from eye to a pixel, compute what that ray intersects, and compute a color for that intersection point.
![](https://wx4.sinaimg.cn/mw690/0071GCRRly1fquryr4se4j30yf0e23yy.jpg)

### Chapter 4
We use spheres in ray tracers, and it's easy to calculate whether a ray hits a sphere.

The ray center from **C=(cx,cy,cz)** to point **p=(x,y,z)** is **(p-C)**.

All the points on the sphere must obey this rule:

**dot((p-c),(p-c))=R*R**

We can use two point to instead of any ray as **p(t)=A+t*B**.

So we get the whole formula:

**t*tdot(B,B)+2*t*dot(B,A-C)+dot(A-C,A-C)-R*R=0**

### Chapter 5
