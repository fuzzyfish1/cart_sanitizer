from django.shortcuts import render
from django.http import HttpResponse
# Create your views here.

def index(request):

    # view function for the site

    context = {}

    # Render the HTML template index.html with the data in the context variable

    return render(request, 'templates/index.html', context=context)

    #return HttpResponse("Hello, world. You're at the polls index.")
