let project = new Project('Shader');

project.addFile('Sources/**');
project.setDebugDir('Deployment');

resolve(project);
