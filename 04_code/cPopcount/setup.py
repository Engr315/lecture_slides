from distutils.core import setup, Extension

def main():
    setup(name="cPopcount",
          version="0.0.1",
          description="Python interface for PopCount",
          author="<your name>",
          author_email="your_email@gmail.com",
          ext_modules=[Extension("cPopcount", 
            ["cPopcount.c","popcount.c" ])])

if __name__ == "__main__":
    main()

